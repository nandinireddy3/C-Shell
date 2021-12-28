#include "main.h"

char* duplicate[100000];
void repeat(char* token[],long long int nargs)
{
    if (nargs <= 2)
    {
        perror("repeat failed");
        return;
    }
    for (int i = 0; i+2 < nargs ; i++)
    {
        duplicate[i] = token[i+2];
    }

    
    if(strcmp(duplicate[0],"cd") == 0)
    {
        for (int j = 0 ; j < atoi(token[1]); j++)
        {
             cd(duplicate,nargs-2);
        }
    }
    else if(strcmp(duplicate[0],"ls") == 0)
    {
        for (int j = 0 ; j < atoi(token[1]); j++)
        {
             ls(duplicate,nargs-2);
        }
    }
    else if(strcmp(duplicate[0],"echo") == 0)
    {
        for (int j = 0 ; j < atoi(token[1]); j++)
        {
             echo(duplicate,nargs-2);
        }
    }
    else if(strcmp(duplicate[0],"pwd") == 0)
    {
        for (int j = 0 ; j < atoi(token[1]); j++)
        {
             pwd();
        }
    }
    else if(!strcmp(duplicate[0],"vi") || !strcmp(duplicate[0],"emacs") || !strcmp(duplicate[0],"gedit") ||
           !strcmp(duplicate[0],"sleep"))
    {
        for (int j = 0 ; j < atoi(token[1]); j++)
        {
             foreground(duplicate);
        }
    }
       
    


}