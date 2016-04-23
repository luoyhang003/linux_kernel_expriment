/*
 * 		lshell.h ---- Description
 *------------------------------------------------------------
 * Date: April 8th, 2016
 * Copyright: Written by Jason Luo - luoyhang003@hotmail.com
 * Function: Head of the project
 *------------------------------------------------------------
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<pwd.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>

#define MAX_PROMPT 1024
#define MAX_ARGS 32
#define MAX_LINE 1024
#define TRUE 1

struct passwd *pwd;
char *buffer;


void get_prompt(char*);
int read_command(char**, char**, char*);
