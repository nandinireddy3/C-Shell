#include "main.h"

void background(char* token[],long long int n)
{
      token[n] = NULL;
      int forkid = fork();
      int pid;
      //int childfork;

    if(forkid < 0)
    {
        perror("ERROR IN FORK OF BACKGROUND PROCESS");
        return;
    }
    else if (forkid == 0)
    {
        
           pid = getpid();
           printf("%d\n",pid);
           
           if (strcmp(token[0], "vim") == 0 || strcmp(token[0], "nano") == 0 || strcmp(token[0], "vi") == 0 || strcmp(token[0],"man") == 0)
           {
             printf(ANSI_COLOR_CYAN "Stopped vim | nano | vi | man  process by SIGSTOP Signal!" ANSI_COLOR_RESET "\n");
             kill(pid,SIGSTOP);
             exit(0);
           }
           int fd = execvp(token[0],token);
           if (fd < 0)
          {
            perror("EXECVP FAILED background");
            return;
          }
          //printf("YES\n");
          //if (strcmp(token[0], "vim") == 0)
            //kill(pid, SIGSTOP);
        //exit(0);
          
    }
    else
    {
        //printf("PARENT PROCESS STARTS\n");
        //sleep(5);
        njobs++;
        //pids[njobs] = forkid;
        //strcpy(names[njobs], token[0]);
        arr_jobs[njobs].pid = forkid;
        strcpy(arr_jobs[njobs].jnames, token[0]);
        //printf("PARENT PROCESS ENDS\n");
    }
}