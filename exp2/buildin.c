/*
 * 		buildin.c ---- Description
 *------------------------------------------------------------
 * Date: April 8th, 2016
 * Copyright: Written by Jason Luo - luoyhang003@hotmail.com
 * Function: Implements of some build-in commands
 *------------------------------------------------------------
 */

 #include "lshell.h"

 int buildin_commands(char *command, char **parameters)
 {
     extern struct passwd *pwd;

     if(strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0)
     {
         exit(0);
     }
     else if(strcmp(command, "version") == 0)
     {
         printf("LShell Version: 1.0\nWritten By luoyhang003(luoyhang003@hotmail.com)\n");
     }
     else if(strcmp(command, "cd") == 0)
     {
        char *cd_path = NULL;

        if(parameters[1] == NULL)
        {
            parameters[1] = malloc(3 * sizeof(char));
            parameters[1][0]= '.';
            parameters[1][1]= '.';
            parameters[1][2]= '\0';
        }
        if(parameters[1][0] == '~')
        {
            cd_path = malloc(strlen(pwd->pw_dir)+strlen(parameters[1]));
            if(cd_path == NULL)
            {
                printf("cd:malloc failed.\n");
            }
            strcpy(cd_path,pwd->pw_dir);
            strncpy(cd_path+strlen(pwd->pw_dir),parameters[1]+1,strlen(parameters[1]));
        }
        else
        {
            cd_path = malloc(strlen(parameters[1]+1));
            if(cd_path == NULL)
            {
                printf("cd:malloc failed.\n");
            }
            strcpy(cd_path,parameters[1]);
        }
        if(chdir(cd_path)!= 0)
            printf("Lshell: cd: %s:%s\n",cd_path,strerror(errno));
        free(cd_path);
     }

     return 0;

 }
