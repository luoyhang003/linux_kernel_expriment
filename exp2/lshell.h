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
struct parse_struct;
char *buffer;


void get_prompt(char*);
int read_command(char**, char**, char*);
int parse(char**, int, struct parse_struct*);

#ifndef PARSE_STRUCT
#define PARSE_STRUCT
#define BACKGROUND 1
#define IN_DIRECT 2
#define OUT_DIRECT 4
#define OUT_DIRECT_APPEND 8
#define IS_PIPED 16
struct parse_struct
{
    int flag;
    char *in_file;
    char *out_file;
    char *another_command;
    char **another_parameters;
};
#endif // PARSE_STRUCT

