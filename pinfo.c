#include "main.h"


void pinfo(char* token[],long long int nargs)
{
    char file[100];
    int pid;
    int pgid;
    char* buffer = (char*)malloc(500*sizeof(char));
    char** strings = (char**)malloc(100*sizeof(char*));
    if (nargs > 2)
    {
        perror("pinfo - TOO MANY ARGS");
        return;
    }
    else if(nargs == 1)   // "pinfo" of shell program
    {
       strcpy(file,"/proc/self/stat");
       pid = getpid();
       pgid = getpgid(pid);
    }
    else if(nargs == 2)  //  "pinfo <pid>"
    {
       strcpy(file,"/proc/");
       strcat(file,token[1]);
       strcat(file,"/stat");
       pid = atoi(token[1]);
       pgid = getpgid(pid);
    }

    int fd = open(file,O_RDONLY);

    if (fd == -1)
    {
        perror("/proc FILE ERROR");
        return;
    }
    else
    {
        read(fd,buffer,500);  // buffer contains status info of process

        strings[0] = strtok(buffer," \n");
        for (int i = 1; i < 52 ; i++)
        {
              strings[i] = strtok(NULL," \n");
        }

        printf("pid -- %d\n",pid);

        //  CODE FOR '+'
        if ((!strcmp(strings[2],"R") || !strcmp(strings[2],"S")) && (pgid == pid) )
            printf("Process Status -- %s+\n",strings[2]);   // foreground process + to be implemented
        
        else
            printf("Process Status -- %s\n",strings[2]);
        

        printf("memory -- %s {Virtual Memory}\n",strings[22]);

      // code for Executable Path
    
             printf("Executable Path -- %s\n",strings[1]);
        
    
     
      

      close(fd);
      free(buffer);
      //free(buffer1);
      free(strings);
    }
}