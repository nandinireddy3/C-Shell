#include "main.h"


void echo(char* token[],long long int n)
{
    long long int i = 1;

    while (i < n-1)
    {
        printf("%s ",token[i]);
        i++;
    }
    if (i == n-1)
    {
      printf("%s",token[n-1]);
      printf("\n");
    }
    

}