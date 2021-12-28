#include "main.h"


char* cmds[100000];
char input[100000];
long long int ID;

//void CTRL_D()
//{

//}
void CTRL_C()
{
    pid_t pid = getpid();

    // background process - return
    if ( pid != ID )
    {
        return;
    } 
    // for a foregound process
    if ( current_foreground.pid != -1)
    {
        kill(current_foreground.pid,SIGINT);
        printf("\n");
    }
    // no foreground process
    if (pid == ID && current_foreground.pid == -1)
    {
        printf("\n");
        Prompt();
        fflush(stdout);
    }
    signal(SIGINT,CTRL_C);
}

void CTRL_Z()
{
     pid_t pid = getpid();

    // background process - return
    if ( pid != ID )
    {
        return;
    } 
    // for a foregound process
    if ( current_foreground.pid != -1)
    {
        njobs++;
        arr_jobs[njobs].pid = current_foreground.pid;
        strcpy(arr_jobs[njobs].jnames,current_foreground.jnames);
        //printf("CTRL-Z\n");
        kill(current_foreground.pid,SIGTTIN);
        kill(current_foreground.pid,SIGTSTP);
        printf("\n");
    }
    // no foreground process
    if (pid == ID && current_foreground.pid == -1)
    {
        printf("\n");
        Prompt();
        fflush(stdout);
    }
    signal(SIGTSTP,CTRL_Z);
} 


int main()
{
    char comargs[10000];
    getcwd(comargs,sizeof(comargs));
    home_directory = comargs;
    pseudohomepid = getpid();
    ID = getpid();
    
    njobs = 0;
    sigkill_flag = 0;
    while (1)
    {
        
        Prompt();
        current_foreground.pid = -1;
        signal(SIGCHLD, print_status);
        signal(SIGINT,CTRL_C);
        signal(SIGTSTP,CTRL_Z);

        fflush(stdin);


    if(fgets(input,100000,stdin) != NULL)
    {
        cmds[0] = strtok(input,";\n");
        long long int n1 = 0;
        while (cmds[n1] != NULL)
        {
            n1++;
            cmds[n1] = strtok(NULL,";\n");
        }

       for ( long long int j = 0 ; j < n1 ; j++)
       {
           long long int n2 = 0;
           char new_cmds[10000];

           strcpy(new_cmds,cmds[j]);
           token[0] = strtok(cmds[j]," \r\n\t");
           while ( token[n2] != NULL)
           {
               n2++;
               token[n2] = strtok(NULL," \r\n\t");
           }

           //*************************************   PIPING    **************************************//
            if(strstr(new_cmds,"|") != NULL)
            {
                PIPE(new_cmds);
                //printf("go on\n");
                continue;
            }
            

          //************************************  PIPING ******************************************//

          // ------------------ Redirection-----------------//
           if(strstr(new_cmds,"<") != NULL || strstr(new_cmds,">>") != NULL || strstr(new_cmds,">") != NULL)
           {
               redirection(new_cmds);
               continue;
           }

           //if (strcmp(token[n2-1],"&") == 0)
          
           //
           if (strcmp(token[0],"cd") == 0)
           {
               cd(token,n2);
           }
           else if (strcmp(token[n2-1],"&") == 0)
           {
              // printf("%s\n",token[n2-1]);
               background(token,n2-1);
           }
           else if (strcmp(token[0],"ls") == 0)
           {
               ls(token,n2);
           }
           else if (strcmp(token[0],"pinfo") == 0)
           {
               pinfo(token,n2);         // process info
           }
           else if (strcmp(token[0],"echo") == 0)
           {
               echo(token,n2);         // echo
           }
           else if(strcmp(token[0],"pwd") == 0)
           {
               pwd();
           }
           else if (strcmp(token[0],"repeat") == 0)
           {
               repeat(token,n2);
           }
           else if(strcmp(token[0],"jobs") == 0)
           {
               Printjobs(token,n2);
           }
           else if(strcmp(token[0],"fg") == 0)
           {
                fg(token,n2);            // makes background process to foreground
           }
           else if(strcmp(token[0],"bg") == 0)
           {
                bg(token,n2);            // makes background process change its state
           }
           else if(strcmp(token[0],"sig") == 0)
           {
                sig(token,n2);            // makes background process change its state
           }
           else
           {
               foreground(token);  // // foreground process
           }
           

           
           
           

       }
    }
    else
    {
        printf("\n");
        printf("STOPPED DUE TO CTRL D\n");
        return 0;
    }
        
        
       
        

       
    }
    
    

    return 0;
}