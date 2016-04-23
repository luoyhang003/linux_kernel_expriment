#include "lshell.h"

void test(void)
{
	char **command = NULL;
	char **parameters;

	char prompt[MAX_PROMPT];
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

        if(-1 == read_command(&command, parameters, prompt))
            break;
	}
//	command
}

int main()
{
    test();
}
