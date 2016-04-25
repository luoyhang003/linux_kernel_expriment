/*
 * 		lshell.h ---- Description
 *------------------------------------------------------------
 * Date: April 8th, 2016
 * Copyright: Written by Jason Luo - luoyhang003@hotmail.com
 * Function: Head of the project
 *------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define MAX_PROMPT 1024
#define MAX_ARGS 20
#define MAX_LINE 4096

struct parse_struct;

struct passwd *pwd;
char *buffer;


void get_prompt(char*);
int read_command(char**, char**, char*);
int parse(char**, int, struct parse_struct*);
int buildin_commands(char*, char**);
void excute(void);
void sig_handler(int signal);

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

