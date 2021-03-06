#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX 1000

void parser(int argc, char *argv[])
{
    char path[512];
    char wholename[512];
    char *nextpiece;

    snprintf(path, 511, "/usr/bin:/bin:/tmp");
    nextpiece = strtok(path, ":");
    printf("next piece = %s\n", nextpiece);
  
    snprintf(wholename, 511, "%s/ls", nextpiece);
    printf("looking for %s\n", wholename);
    if(access(wholename, X_OK) == 0)
    {
        printf("yey\n");
    }
   
    while(nextpiece != NULL)
    {
        nextpiece = strtok(NULL, ":");
        printf("next_piece = %s\n", nextpiece);
        snprintf(wholename, 511, "%s/ls", nextpiece);
        printf("looking for %s\n", wholename);
        if(access(wholename, X_OK) == 0)
        {
            printf("yey\n");
        }
    }
}

int main(int argc, char **argv)
{
    char *line = NULL;
    size_t linesize = 0;
    ssize_t linelen;
    char buf[MAX];
    char *path = "/bin/";
    char command[20];
    char program[50];
    pid_t pid = 0;
    //printf("shell> ");
    while((linelen = getline(&line, &linesize, stdin)) != -1)
    {
        if(strncmp("exit", line, 4) == 0)
        {
            // user wants to exit
            exit(0);
        }
        else if(strncmp("cd", line, 2) ==0)
        {
            line = line+3;
            printf(line); 
            chdir(line); 
            //printf('\n');   
        }
        else
        {
            fwrite(line, linelen, 1, stdout);
            strncpy(command, line, (strlen(line)-1));
            strcpy(program, path);
            strcat(program, command);
            // fork
            pid = fork();
            // if child, exec
            if(pid == 0)
            {
                 execv(program, command);
                 printf("CHILD PROCESS");          
                
            }
            // if parent, wait
            else
            {
                 printf("PARENT PROCESS");
                 wait (NULL);
            }
        }
    }
    free(line);
    if(ferror(stdin))
    {
        err(1, "getline");
    }
}
