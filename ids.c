#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "ids.h"
/* Syslog Buffer size */
#define SYS_LOG_BUFF_SIZE   (1000000)

typedef enum
{
  PRIO_HIGH = 0,
  PRIO_MEDIUM,
  PRIO_LOW
}tEventTypes;

typedef struct
{
  tEventTypes type;
  char * eventString;
  int eventStringSeize;
}tEventReportType;


/* Buffer Containning syslog Data */
char sysLogBuff[SYS_LOG_BUFF_SIZE];

/* Callback function to be called by OSAL Layer for logging events from other OCU Components */
extern void IdsReportEvent(void* event)
{
  /* TODO: Pending Integration of OSAL layer */
}

/* Periodic Function to fetsch Syslog for Events */
extern void IdsAnalyseSysLog(char* syslogPath)
{
  /* Char count , will be used for read contents of syslog */
  int charCount;
  /* Open syslog file for reading */
  int fildesSyslog = open(syslogPath, O_RDONLY);
  /* Read syslog */
  if(charCount = read(fildesSyslog,sysLogBuff, SYS_LOG_BUFF_SIZE))
  {
    /* Open file for writing */
    int filedesOut = open("/home/iwahdan/Ids.log", O_WRONLY | O_APPEND | O_CREAT);

    if(filedesOut)
    {
      /* Write Log to file */
      write(filedesOut, sysLogBuff, charCount);
    }
    close(filedesOut);
  }
  close(fildesSyslog);
}
