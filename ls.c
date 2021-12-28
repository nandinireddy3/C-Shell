#include "main.h"

char path[100000];
char minipath[50000];

void printls()
{
      struct stat pers;
                if( stat(minipath,&pers) == -1)
                {
                    perror("ERROR IN STAT");
                    return;
                }
                 
            printf((S_ISDIR(pers.st_mode)) ? "d" : "-");
            printf((pers.st_mode & S_IRUSR) ? "r" : "-");
            printf((pers.st_mode & S_IWUSR) ? "w" : "-");
            printf((pers.st_mode & S_IXUSR) ? "x" : "-");
            printf((pers.st_mode & S_IRGRP) ? "r" : "-");
            printf((pers.st_mode & S_IWGRP) ? "w" : "-");
            printf((pers.st_mode & S_IXGRP) ? "x" : "-");
            printf((pers.st_mode & S_IROTH) ? "r" : "-");
            printf((pers.st_mode & S_IWOTH) ? "w" : "-");
            printf((pers.st_mode & S_IXOTH) ? "x" : "-");


                struct passwd *pwd;
                pwd = getpwuid(pers.st_uid);

                struct group *grp;
                grp = getgrgid(pers.st_gid);
                
                char date[30];
                strftime(date, sizeof(date), "%b  %d %H:%M", localtime(&pers.st_mtime));

    printf("  %-6ld%-8s%-8s%-8ld%-14s", pers.st_nlink, pwd->pw_name, grp->gr_name, pers.st_size, date);
}
void ls_eachfile(int a, int l,int dir_i)
{
    struct dirent **namelist;
    int nofiles;
    nofiles = scandir(path,&namelist,NULL,alphasort);
      
      if(nofiles == -1 && open(path,O_RDONLY) != -1)
      {
          printf(" %s\n",path);
          //close(path);
          return;
      }

      if(nofiles == -1)
      {
          perror("ls");
          return;
      }

      if(dir_i > 1){
        printf("%s:\n", path);
    }

      if (a == 0)
      {
          if (l == 0) {
              for (long long int i = 0; i < nofiles;i++)
              {
                  if(namelist[i]->d_name[0] != '.')
                  printf("%s \n",namelist[i]->d_name);
              }

        }
          else if (l == 1){
            for (long long int i = 0; i < nofiles;i++)
           {
             if(namelist[i]->d_name[0] != '.')
               {
                  strcpy(minipath,"");
                 strcpy(minipath,path);
                 strcat(minipath,"/");
                 strcat(minipath,namelist[i]->d_name);

                   printls();
                   printf(" %s\n", namelist[i]->d_name);
               }
             
            }

            if (dir_i > 1)
                printf("\n");
           
          }
      }
      else if (a == 1)
      {
         if (l == 0){
            for (long long int i = 0; i < nofiles;i++)
              {
                  printf("%s \n",namelist[i]->d_name);
              }

          }
          else if (l == 1){
            
          for (long long int i = 0; i < nofiles;i++)
           {
                 strcpy(minipath,"");
                 strcpy(minipath,path);
                 strcat(minipath,"/");
                 strcat(minipath,namelist[i]->d_name);
                
                printls();
                 printf(" %s\n", namelist[i]->d_name);

           }
           if (dir_i > 1)
                printf("\n");
           


          }
      }
}
void ls(char* token[],long long int nargs)          //  command , no of args of are input
{
    int dir_i;                  
    long int totalflags;

    int l = 0 ; 
    int a = 0;

    if (nargs == 1)
    {
        getcwd(cwd,sizeof(cwd));
        strcpy(path, cwd);
        strcat(path, "/.");
        ls_eachfile(0, 0, 1);
        return;
    }
    else
    {
         totalflags = 0;

        for (long long int i = 1; i < nargs ; i++ )
        {
            if (token[i][0] == '-'){
                
                totalflags += 1;
                if(strcmp(token[i],"-l") == 0)
                   l = 1;
                else if(strcmp(token[i],"-a") == 0)
                   a = 1;
                else if(!strcmp(token[i],"-la") || !strcmp(token[i],"-al"))
                {
                    l = 1; a = 1; 
                }
                else
                {
                    perror("INCORRECT FLAG FAILURE");
                    return;
                }
            }
        } 
       
       dir_i = nargs-1-totalflags;                  // number of directories
       for (long long int i = 1; i < nargs ; i++ )
       {
           if (token[i][0] != '-')
           {
               if (token[i][0] == '~')
               {
                   strcpy(path,home_directory);
                   strcat(path,&token[i][1]);
               }
               else
               {
                   strcpy(path,token[i]);
               }
            

              ls_eachfile(a,l,dir_i);
           }
       }

       //printf("dir_i = %d, totalflags = %ld , nargs = %lld",dir_i,totalflags,nargs);
       getcwd(cwd,sizeof(cwd));      // if only flags are present //     // ls -l//  // ls -a// ...
       if(dir_i == 0){
            strcpy(path, cwd);
            strcat(path, "/.");
            ls_eachfile(a, l, 1);
        }

    }

      

    


}