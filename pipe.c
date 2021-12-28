#include "main.h"

long long int split_it(char *list[], char *command, char *delim){
    
    long long int n = 0; 
    list[0] = strtok(command, delim);
    while (list[n] != NULL)
    {
        n++;
        list[n] = strtok(NULL, delim);
    }
    return n;
}

void Execute(char* list_command)
{
    char* tokenize[1000];
    //char cmd[2000];
    //strcpy(cmd,list_command);   // 
    long long int n_curr_com = 0;
    n_curr_com = split_it(tokenize,list_command," \t\n\r");

          if (strcmp(tokenize[0],"cd") == 0)
           {
               cd(tokenize,n_curr_com);
           }
           else if (strcmp(tokenize[n_curr_com-1],"&") == 0)
           {
              // printf("%s\n",token[n_curr_com-1]);
               background(tokenize,n_curr_com-1);
           }
           else if (strcmp(tokenize[0],"ls") == 0)
           {
               ls(tokenize,n_curr_com);
           }
           else if (strcmp(tokenize[0],"pinfo") == 0)
           {
               pinfo(tokenize,n_curr_com);         // process info
           }
           else if (strcmp(tokenize[0],"echo") == 0)
           {
               echo(tokenize,n_curr_com);         // echo
           }
           else if(strcmp(tokenize[0],"pwd") == 0)
           {
               pwd();
           }
           else if (strcmp(tokenize[0],"repeat") == 0)
           {
               repeat(tokenize,n_curr_com);
           }
           else if(strcmp(tokenize[0],"jobs") == 0)
           {
               Printjobs(tokenize,n_curr_com);
           }
           else if(strcmp(tokenize[0],"fg") == 0)
           {
                fg(tokenize,n_curr_com);            // makes background process to foreground
           }
           else if(strcmp(tokenize[0],"bg") == 0)
           {
                bg(tokenize,n_curr_com);            // makes background process change its state
           }
           else
           {
               foreground(tokenize);  // // foreground process
           }
}
void PIPE(char* comm)
{
    long long int n_commando = 0;
    char* commando[2000];

    int fd[2];
    int forkid,input = 0;
    n_commando = split_it(commando,comm,"|");

    long long int k = 0;
    while( k < n_commando)
    {
        pipe(fd);
        forkid = fork();

        if (forkid < 0)
        {
            perror("Error in Forking of Pipe");
            return;
        }
        else if(forkid == 0)
        {
            //printf("YES\n");
           dup2(input,0);

           if (k < n_commando-1)
               dup2(fd[1],1);
           

           close(fd[0]);
           if(strstr(commando[k],">") != NULL || strstr(commando[k],"<") != NULL)
           {
               redirection(commando[k]);
           }
           else
           {
               Execute(commando[k]);
           }
           exit(1);

        }
        else
        {
            wait(NULL);
            close(fd[1]);
            input = fd[0];
        }
        k++;
    }
}