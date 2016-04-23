/*
 * 		readcmd.c ---- Description
 *------------------------------------------------------------
 * Date: April 21th, 2016
 * Copyright: Written by Jason Luo - luoyhang003@hotmail.com
 * Function: Reading commands from the Shell
 *------------------------------------------------------------
 */


#include "lshell.h"
#include <readline/readline.h>
#include <readline/history.h>

int read_command(char **command, char **parameters, char *prompt)
{
	free(buffer);
	buffer = readline(prompt);
	if(feof(stdin))
	{
		printf("\n");
		exit(0);
	}

	if(buffer[0] == '\0')
	{
		return -1;
	}

	int count = 0;
	char *start, *end;
	int isFinished = 0;

	start = end = buffer;

	while(isFinished == 0)
	{
		while((*start == ' ' && *end == ' ') || (*start == '\t' && *end == '\t'))
		{
			start++;
			end++;
		}

		if(*end == '\0' || *end == '\n')
        {
            if(count == 0)
            {
                return -1;
            }
            break;
        }

        while(*end != '\0' && *end != '\n' && *end != ' ')
        {
            end++;
        }

        if(count == 0){
            char *p = end;
            *command = start;

            while(p != start && *p != '/'){
                p--;
            }

            if(*p == '/'){
                p++;
            }

            parameters[0] = p;
            count += 2;

#ifdef DEBUG
            printf("\ncommand:%s\n", *command);
#endif // DEBUG
        }
        else if(count <= MAX_ARGS){
            parameters[count-1] = start;
            count++;
        }
        else{
            break;
        }

        if(*end = '\0' || *end == '\n'){
            *end = '\0';
            isFinished = 1;
        }
        else{
            *end = '\0';
            end++;
            start = end;
        }


	}
	parameters[count-1] = NULL;
#ifdef DEBUG
    printf("input analysis:\n");
    printf("command:[%s]\ncommand:[%s]\nparameters:\n",*command,parameters[0]);
    int i;
    for(i=0;i<count-1;i++)
        printf("[%s]\n",parameters[i]);
#endif
	return count;
}


