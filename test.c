#include <stdio.h>
#include "logger.h"
int main()
{
   
  int x = 199,i=0;
  char *s = "Bitter Truth";
 
  while(i<5)
  {
   log_print(3,4,__FILE__,__LINE__,"Hello World ");
   log_print(4,4,__FILE__,__LINE__,"Zing is back !!! %s %d",s,x++);
   i++;
  }
}
