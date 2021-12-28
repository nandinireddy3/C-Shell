#include "main.h"
#include <sys/utsname.h>

char dest[20000];
char dir[10000];



void displayPrompt()
{
    
    int k = 0;
    char hostname[200];
    char username[200];
    
    gethostname(hostname, sizeof(hostname));
    if(gethostname(hostname, sizeof(hostname)) != 0)
    {
        perror("gethostname(): ");
        return;
    }


    getlogin_r(username, sizeof(username));
    if(getlogin_r(username, sizeof(username)) != 0)
    {
        perror("getlogin_r(): ");
        return;
    }

    getcwd(cwd, sizeof(cwd));
    
    if (strcmp(cwd,home_directory) == 0)
    {
        strcpy(dir,"~");
    }
    else if(strstr(cwd,home_directory))
    {
        strcpy(dir,"~");
        strcat(dir,strstr(cwd,home_directory)+strlen(home_directory));

    }
    else
    {
        chdir(cwd);
        strcpy(dir,cwd);
    }


    strcpy(dest,"<");

    
    strcat(dest,username);          // USERNAME REQUIRED
    strcat(dest,"@");
    strcat(dest,hostname);
    strcat(dest,":");

    strcat(dest,dir);
    strcat(dest,">");
    printf("\033[1;32m");
    printf("%s",dest);
    printf("\033[0m");
    
   
    
}

void Prompt()
{
    displayPrompt();
    
    

    
    
    
}

