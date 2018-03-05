#include <stdio.h>
#include "ids.h"
#include <unistd.h>

int main()
{
  int Data = 0;
  /* first Clear log */
  IdsClearLog();

  while(1)
  {
    Data = IdsAnalyseSysLog("/var/log/syslog");
    printf("Log Sync Done! (Data synced = %d bytes)\n", Data);
    usleep(5000000);
  }
}
