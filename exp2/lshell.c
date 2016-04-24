#include "lshell.h"

void test(void)
{
	char **command = NULL;
	char **parameters;

	int num_para;

	char prompt[MAX_PROMPT];
	struct parse_struct info;
//	get_prompt(prompt);
#ifdef DEBUG
	printf("TEST:%s\n", prompt);
#endif // DEBUG
	parameters = malloc(sizeof(char*) * (MAX_ARGS+2));
	buffer = malloc(sizeof(char) * MAX_LINE);
	if(parameters == NULL || buffer == NULL){
        printf("lShell Error: Malloc Failed!\n");
        return;
	}
	while(TRUE){
        get_prompt(prompt);

        num_para = read_command(&command, parameters, prompt);

        if(-1 == num_para)
        {
            continue;
        }
        num_para--;
        parse(parameters, num_para, &info);

	}
//	command
}

int main()
{
    test();
}
