/*
 * 		parse.c ---- Description
 *------------------------------------------------------------
 * Date: April 24th, 2016
 * Copyright: Written by Jason Luo - luoyhang003@hotmail.com
 * Function: Parsing the commands
 *------------------------------------------------------------
 */

 #include "lshell.h"

 int parse_init(struct parse_struct *info)
 {
    info->flag = 0;
    info->in_file = NULL;
    info->out_file = NULL;
    info->another_command = NULL;
    info->another_parameters = NULL;
    return 0;
 }


 int parse(char **parameters, int num_para, struct parse_struct *info)
 {
     int i;
     parse_init(info);
     if(strcmp(parameters[num_para-1],"&") == 0)
     {
        info->flag |= BACKGROUND;
        parameters[num_para-1] = NULL;
        num_para--;
     }
     for(i = 0; i < num_para;)
     {
         if(strcmp(parameters[i], "<<") == 0 || strcmp(parameters[i], "<") == 0)
         {
             info->flag |= IN_DIRECT;
             info->in_file = parameters[i+1];
             parameters[i] = NULL;
             i+=2;
         }
         else if(strcmp(parameters[i], ">") == 0)
         {
             info->flag |= OUT_DIRECT;
             info->out_file = parameters[i+1];
             parameters[i] = NULL;
             i+=2;
         }
         else if(strcmp(parameters[i], ">>") == 0)
         {
             info->flag |= OUT_DIRECT_APPEND;
             info->out_file = parameters[i+1];
             parameters[i] = NULL;
             i+=2;
         }
         else if(strcmp(parameters[i], "|") == 0)
         {
             info->flag |= IS_PIPED;
             char *p;
             parameters[i] = NULL;
             info->another_command = parameters[i+1];
             info->another_parameters = &parameters[i+1];
             for(p = info->another_parameters[0] + strlen(info->another_parameters[0]);
                 p != &(info->another_parameters[0][0]) && *p != '/';
                 p--);
             if(*p == '/')
             {
                 p++;
             }
             info->another_parameters[0] = p;
             break;
         }
         else
         {
             i++;
         }
     }

#ifdef DEBUG
printf("\n========PARSING=========\n");
printf("BACKGROUND:%s\n", info->flag & BACKGROUND ? "YES":"NO");
printf("INDREICT:");
info->flag & IN_DIRECT ? printf("YES, FILE:%s\n", info->in_file) : printf("NO\n");
printf("OUTDIRECT:");
info->flag & OUT_DIRECT ? printf("YES, FILE:%s\n", info->out_file) : printf("NO\n");
printf("OUTDIRECT_APPEND");
info->flag & OUT_DIRECT_APPEND ? printf("YES, FILE:%s\n", info->out_file) : printf("NO\n");
printf("PIPE:");
info->flag & IS_PIPED ? printf("YES, COMMAND:%s %s %s\n", info->another_command, info->another_parameters[0], info->another_parameters[1]) : printf("NO\n");
#endif // DEBUG

     return 1;
 }
