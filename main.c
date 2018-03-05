#include <stdio.h>
#include "ids.h"
extern void IdsAnalyseSysLog(char* syslogpath);
int main()
{
  printf("Reading Sys Log .....");
  IdsAnalyseSysLog("/var/log/syslog");
  printf("\n\n Completed!");
}
