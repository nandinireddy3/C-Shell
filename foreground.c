#include "main.h"

void foreground(char* token[])
{
    int forkid = fork();
    current_foreground.pid = forkid;
    strcpy(current_foreground.jnames,token[0]);

    if(forkid < 0)
    {
        perror("ERROR IN FORK OF FOREGROND PROCESS");
        return;
    }
    else if (forkid == 0)
    {
        int fd = execvp(token[0],token);
        if (fd < 0)
        {
            perror("EXECVP FAILED Foreground");
            return;
        }
    }
    else
    {
        //printf("PARENT PROCESS STARTS\n");
        int status;
        waitpid(forkid,&status,WUNTRACED);

        //wait(NULL);
        //printf("PARENT PROCESS ENDS\n");
    }
}