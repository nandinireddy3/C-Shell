#include "main.h"

long long int split(char *list[], char *command, char *delim){
    
    long long int n = 0; 
    list[0] = strtok(command, delim);
    while (list[n] != NULL)
    {
        n++;
        list[n] = strtok(NULL, delim);
    }
    return n;
}

void execute(char* list_command)
{
    char* tokenize[1000];
    //char cmd[2000];
    //strcpy(cmd,list_command);   // 
    long long int n_curr_com = 0;
    n_curr_com = split(tokenize,list_command," \t\n\r");

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

void redirection(char* command) // nargs = argc of command
{
    //printf("command is %s\n",command);
    int in = 0;
    int out = 0;
    int app = 0, in_fd,out_fd ,forkid;

    char* out_file = NULL;
    char* in_file = NULL;

    char* out_list[2];
    char* in_list[2];

    in_list[0] = command;   //

    int stdout_Real = dup(STDOUT_FILENO);
    int stdin_Real = dup(STDIN_FILENO);

    if(strstr(command,"<") != NULL)
         in = 1;
      
    if(strstr(command,">>") != NULL)
       app = 1;
    else if(strstr(command,">") != NULL) 
       out = 1;
       
    

    if (out == 1 || app == 1)
    {
        out_list[0] = strtok(command,">");
        out_list[1] = strtok(NULL,">");
        in_list[0] = out_list[0]; //
    }

    if(in == 1)
    {
        in_list[0] = strtok(in_list[0],"<");
        in_list[1] = strtok(NULL,"<");
    }

    forkid = fork();

    if(forkid < 0)
    {
        perror("ERROR IN REDIRECTION FORK");
        return;
    }
    else if (forkid == 0)
    {
        if(in == 1)
        {
            in_file = strtok(in_list[1]," \n\t\r");

            if (in_file == NULL)
            {
                perror("Input File not Specified");
                return;
            }

            in_fd = open(in_file,O_RDONLY);

            if (in_fd >= 0)
            {
                dup2(in_fd,0);
                close(in_fd);
            }
            else
            {
                perror("Input file does not open");
                return;
            }
        }
        if (out == 1 || app == 1)
        {
            out_file = strtok(out_list[1]," \n\t\r");

            if (out_file == NULL)
            {
                perror("Output File not Specified");
                return;
            }

          out_fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644); 

          if (out_fd >=0 )
          {
              dup2(out_fd,1);
              close(out_fd);
          }  
          else
            {
                perror("output file does not open");
                return;
            }
        }

        if (strstr(in_list[0],">") != NULL || strstr(in_list[0],"<") != NULL)
        {
            redirection(in_list[0]);
        }
        else
         execute(in_list[0]);

        dup2(stdin_Real,0);
        close(stdin_Real);
        dup2(stdout_Real,1);
        close(stdout_Real);
    }
    else
    {
        int status;
        while(wait(&status) != forkid)
        ;
    }

    return;
}