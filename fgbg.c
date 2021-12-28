#include "main.h"

void deleteProcess(int pid)
{
     if (pid == -1)
            njobs = 0;
          else
          {
             for (int k = 1; k <= njobs; k++)
            {
                if (arr_jobs[k].pid == pid)
                {
                    for (int j = k; j < njobs; j++){
                       // printf("REMOVING\n %d .. %s",arr_jobs[k].pid,arr_jobs[k].jnames);
                        arr_jobs[j].pid = arr_jobs[j + 1].pid;
                        strcpy(arr_jobs[j].jnames, arr_jobs[j+1].jnames);
                    }
                     njobs -= 1;
                }
               
            }
          }
}

void fg(char* command[],long long int nargs)
{
    long long int flag = 0;
    
      if (nargs != 2)
       {
           printf("fg incorrect no.of args\n");
           return;
       }

    if (atoi(command[1]) <= njobs && atoi(command[1]) >= 1)
    {
        int status;
        signal(SIGTTIN,SIG_IGN);
        signal(SIGTTOU,SIG_IGN);
        tcsetpgrp(STDIN_FILENO,arr_jobs[atoi(command[1])].pid);
        current_foreground.pid = arr_jobs[atoi(command[1])].pid;
        strcpy(current_foreground.jnames,arr_jobs[atoi(command[1])].jnames);
        flag = -1;
        kill(arr_jobs[atoi(command[1])].pid,SIGCONT);
        // delete from jobs
        deleteProcess(arr_jobs[atoi(command[1])].pid);
        waitpid(-1, NULL, WUNTRACED);   // WAITING FOR THAT PROCESS TO FINISH EXECUTION
        tcsetpgrp(STDIN_FILENO,getpgrp());
        signal(SIGTTIN,SIG_DFL);
        signal(SIGTTOU,SIG_DFL);

    }
    if (flag == 0)
    {
        printf("NO SUCH PROCESS EXISTS\n");
    }
}
void bg(char* command[],long long int nargs)
{
    if (nargs != 2)
       {
           printf("bg incorrect no.of args\n");
           return;
       }
    
    long long int num=atoi(command[1]);
    long long int flag=0;
    for(long long int i=1; i<=njobs; i++)
    {
        if(i==num)
        {
            flag=1;
            kill(arr_jobs[num].pid, SIGTTIN);  
            kill(arr_jobs[num].pid,SIGCONT);
        }
    }
    if(flag==0)
        printf("Error: No such job Exists\n");
}