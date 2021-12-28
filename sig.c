#include "main.h"

void sig(char* command[],long long int nargs)
{
    if (nargs != 3)
    {
        printf("Error in no.of args in sig\n");
        return;
    }
    int jobnum = atoi(command[1]);
    int signo = atoi(command[2]);

    if (jobnum <= njobs && jobnum > 0)
    {
        if (signo == 9)
        sigkill_flag = 1;

        kill(arr_jobs[jobnum].pid,signo);
    }  
    else
    {
        printf("No such process found \n");
        return;
    }
}