#include "main.h"

char olddir[1000] = "";

void cd(char* token[],long long int nargs)
{
    if(nargs > 2)
    {
        perror("TOO MANY ARGUMENTS");
    }
    else if (nargs == 1)
    {
        getcwd(olddir,sizeof(olddir));
        chdir(home_directory);
    }
    else if (nargs == 2)
    {
        char path[10000];

        strcpy(path,token[1]);

        if (strcmp(path,"~") == 0)
        {
            getcwd(olddir,sizeof(olddir));
            chdir(home_directory);
            return;
        }
        else if (strcmp(path,"-") == 0)
        {
             chdir(olddir);
             printf("%s\n",olddir);
             getcwd(olddir,sizeof(olddir));
        }
        else 
        {
            int check = chdir(path);

            if (check == -1)
            {
              printf("\033[0;31mError: Invalid path\033[0m\n");
              perror("cd");
            }
            getcwd(olddir,sizeof(olddir));
            
        }
        
        
        
    }
    
    
}