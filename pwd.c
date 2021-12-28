#include "main.h"

char buf[1000000];
void pwd()
{
  getcwd(buf, sizeof(buf));
  printf("%s\n", buf);
}

// *****PID********//