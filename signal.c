#include "main.h"

void print_status(){
    
    int status;
    long long int pid;

    pid = waitpid(-1, &status, WNOHANG);

    for (int i = 1; i <= njobs; i++)
    {

        int x = WEXITSTATUS(status);
        int y = WIFEXITED(status);


        if(((y != 0) && pid == arr_jobs[i].pid) || (sigkill_flag == 1 && pid == arr_jobs[i].pid) ){

            if(sigkill_flag == 1)
               sigkill_flag = 0;

            if(x == 0){
                fprintf(stderr, "\n%s with pid %lld exited normally\n", arr_jobs[i].jnames, pid);
            }
            else{
                fprintf(stderr, "\n %s with pid %lld exited with status = %d\n", arr_jobs[i].jnames, pid, y);
            }
            Prompt();
            fflush(stdout);
           // return;

            // remove from jobs
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
    }
}