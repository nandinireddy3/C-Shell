#include "main.h"

// struct to print ascending order of names
struct Asc_Names
{
    long long int jobno;
    char Fnames[10000];
};

struct Asc_Names INFO[1000];

void Stringswap(char* x,char* y)
{
    char temp[1000];
    strcpy(temp,x);
    strcpy(x,y);
    strcpy(y,temp);
}

void LexicOrder(struct Asc_Names INFO[])
{
     for (int i = 1; i <= njobs; ++i) {
      for (int j = i + 1; j <= njobs ; ++j) {

         // swapping strings if they are not in the lexicographical order
         if (strcmp(INFO[i].Fnames, INFO[j].Fnames) > 0) {
             Stringswap(INFO[i].Fnames, INFO[j].Fnames);
            // Intswap(&INFO[i].jobno, &INFO[j].jobno);
            long long int temp = INFO[i].jobno;
            INFO[i].jobno = INFO[j].jobno;
            INFO[j].jobno = temp; 
         }
      }
   }
}
void Printjobs(char* command[],long long int nargs)
{
    for (long long int i = 1; i <= njobs; i++)
    {
        INFO[i].jobno = i;
        strcpy(INFO[i].Fnames,arr_jobs[i].jnames);
    }
    LexicOrder(INFO);   // INFO[1], INFO[2] ,INFO[3] ,... -> ASCENDING ORDER OF NAMES
    // INFO[i].jobno is jobno acc to Ascending order of names.

    for(long long int i = 1; i <= njobs ; i++)
    {
       long long int pid = arr_jobs[INFO[i].jobno].pid;
        char name[10000],status;
        strcpy(name,INFO[i].Fnames);
          
        char file[1000];  
        sprintf(file,"/proc/%lld/stat",pid);

        FILE *fd;
        fd = fopen(file,"r");

        if(fd < 0)
            perror("Error: no such process exists\n");
        else
        {
            fscanf(fd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status);
            fclose(fd);
        }

      if (nargs == 1)
      {
        if (status == 'T')
             printf("[%lld] Stopped %s [%lld]\n",INFO[i].jobno, name,pid);
        else
            printf("[%lld] Running %s [%lld]\n",INFO[i].jobno, name,pid);
      } 
      else if (nargs == 2)
      {
          if (strcmp(token[1],"-r") == 0)
          {
              if (status != 'T')
                 printf("[%lld] Running %s [%lld]\n",INFO[i].jobno, name,pid);
          }
          else if (strcmp(token[1],"-s") == 0)
          {
              if (status == 'T')
                 printf("[%lld] Stopped %s [%lld]\n",INFO[i].jobno, name,pid);
          }
          
      }   

       
    }


}