#include "lshell.h"

#define MAXPID 1024
#define TRUE 1

pid_t PIDTABLE[MAXPID];

void sig_handler(int signal)
{
    pid_t pid;
    int index;
    for(index = 0; index < MAXPID; index++)
    {
        if(PIDTABLE[index] != 0)
        {
            pid = waitpid(PIDTABLE[index], NULL, WNOHANG);
            if(pid > 0)
            {
                PIDTABLE[index] = 0;
            }
            else if(pid < 0)
            {
                if(errno != ECHILD)
                    perror("waitpid() error!");
            }
        }
    }
    return;
}

void execute(void)
{
	char *command = NULL;
	char **parameters;

	int num_para;
	int status, i;

	char prompt[MAX_PROMPT];
	struct parse_struct info;

	pid_t child1, child2;


	parameters = malloc(sizeof(char *) * (MAX_ARGS+2));
	buffer = malloc(sizeof(char) * MAX_LINE);
	if(parameters == NULL || buffer == NULL){
        printf("lShell Error: Malloc Failed!\n");
        return;
	}

	if(signal(SIGCHLD, sig_handler) == SIG_ERR)
    {
        perror("signal error");
    }

	while(TRUE){
        int pipe_fd[2], in_fd, out_fd;

        get_prompt(prompt);

#ifdef DEBUG
printf("PROMPT:%s\n", prompt);
#endif // DEBUG
        num_para = read_command1(&command, parameters, prompt);

        if(-1 == num_para)
        {
            continue;
        }
        num_para--;
        parse(parameters, num_para, &info);

        if(buildin_commands(command, parameters))
        {
            continue;
        }

        if(info.flag & IS_PIPED)
        {
            if(pipe(pipe_fd) < 0)
            {
                printf("LShell Error: pipe created failed!\n");
                exit(0);
            }
        }

        if((child1 = fork()) != 0)
        {
            if(info.flag & IS_PIPED)
            {
                if((child2 = fork()) == 0)
                {
                    close(pipe_fd[1]);
                    close(fileno(stdin));
                    dup2(pipe_fd[0], fileno(stdin));
                    close(pipe_fd[0]);
                    execvp(info.another_command, info.another_parameters);
                }
                else
                {
                    close(pipe_fd[0]);
                    close(pipe_fd[1]);
                    waitpid(child2, &status, 0);
                }

                if(info.flag & BACKGROUND)
                {
                    int index;
                    for(index = 0; index < MAXPID; index++)
                    {
                        if(PIDTABLE[i] == 0)
                        {
                            PIDTABLE[i] = child1;
                        }
                    }
                    if(index == MAXPID)
                    {
                        perror("LShell Error: Too much processes!\n");
                    }

                }
                else
                {
                    waitpid(child1, &status, 0);
                }
            }
            else
            {
                if(info.flag & IS_PIPED)
                {
                    if(!(info.flag & OUT_DIRECT) && !(info.flag & OUT_DIRECT_APPEND))
                    {
                        close(pipe_fd[0]);
                        close(fileno(stdout));
                        dup2(pipe_fd[1], fileno(stdout));
                        close(pipe_fd[1]);
                    }
                    else
                    {
                        close(pipe_fd[0]);
                        close(pipe_fd[1]);
                        if(info.flag & OUT_DIRECT)
                        {
                            out_fd = open(info.out_file, O_WRONLY|O_CREAT|O_TRUNC, 0666);
                        }
                        else
                        {
                            out_fd = open(info.out_file, O_WRONLY|O_APPEND|O_TRUNC, 0666);
                        }
                        close(fileno(stdout));
                        dup2(out_fd, fileno(stdout));
                        close(out_fd);
                    }
                }
                else
                {
                    if(info.flag & OUT_DIRECT)
                    {
                        out_fd = open(info.out_file, O_WRONLY|O_CREAT|O_TRUNC, 0666);
                        close(fileno(stdout));
                        dup2(out_fd, fileno(stdout));
                        close(out_fd);
                    }
                    if(info.flag & OUT_DIRECT_APPEND)
                    {
                        out_fd = open(info.out_file, O_WRONLY|O_CREAT|O_APPEND, 0666);
                        close(fileno(stdout));
                        dup2(out_fd, fileno(stdout));
                        close(out_fd);
                    }
                }
                if(info.flag & IN_DIRECT)
                {
                    in_fd = open(info.in_file, O_CREAT|O_RDONLY, 0666);
                    close(fileno(stdin));
                    dup2(in_fd, fileno(stdin));
                    close(in_fd);
                }
                execvp(command, parameters);
            }
        }

	}
    free(parameters);
    free(buffer);
}

int main()
{
    int i;
    for(i = 0; i < MAXPID; i++)
    {
        PIDTABLE[i] = 0;
    }
    execute();
    return 0;
}
