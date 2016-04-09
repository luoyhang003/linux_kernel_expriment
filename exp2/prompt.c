/*
 * 		prompt.c ---- Description
 *------------------------------------------------------------
 * Date: April 8th, 2016
 * Copyright: Written by Jason Luo - luoyhang003@hotmail.com
 * Function: Promption of the Shell
 *------------------------------------------------------------
 */

#include"lshell.h"

const int max_name_len = 256;
const int max_path_len = 1024;

void get_prompt(char *prompt)
{
	extern struct passwd *pwd;
	char hostname[max_name_len];
	char pathname[max_path_len];
	int prompt_length;

	pwd = getpwuid(getuid());
	getcwd(pathname, max_path_len);
//	printf("%s\n%s", pwd->pw_name, pwd->pw_dir);

	if(gethostname(hostname, max_path_len) == 0)
	{
		sprintf(prompt, "lshell>%s@%s:", pwd->pw_name, hostname);
	}
	else
	{
		sprintf(prompt, "lshell>%s@unknown:", pwd->pw_name);
	}
	prompt_length = strlen(prompt);

//	if(strlen(pathname) < strlen(pwd->pw_dir)) {printf("%s\n%s\n",pathname, pwd->pw_dir);}
	
	if(strlen(pathname) < strlen(pwd->pw_dir) || (strncmp(pathname, pwd->pw_dir, strlen(pwd->pw_dir))) != 0)
	{
		sprintf(prompt + prompt_length, "%s", pathname);
	}
	else
	{
		sprintf(prompt + prompt_length, "~%s", pathname + strlen(pwd->pw_dir));
	}
	prompt_length = strlen(prompt);
	if(geteuid() != 0)
	{
		sprintf(prompt + prompt_length, "$");
	}
	else
	{
		sprintf(prompt + prompt_length, "#");
	}
	return;
}

