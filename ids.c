#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "ids.h"
/* Syslog Buffer size */
#define SYS_LOG_BUFF_SIZE   (1)

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
extern int IdsAnalyseSysLog(char* syslogPath)
{
  /* File offset accumulator for reading new logs */
  static int logOffset = 0;
  /* Char writen Count */
  int charCount = 0;
  /* Open syslog file for reading */
  int fildesSyslog = open(syslogPath, O_RDONLY);
  /* Open file for writing */
  int filedesOut = open("/home/iwahdan/Ids.log", O_WRONLY | O_APPEND | O_CREAT);
  /* move offset to last read Data */
  lseek(fildesSyslog,logOffset, SEEK_CUR );
  /* Read syslog */
  while((read(fildesSyslog,sysLogBuff, 1)) && filedesOut)
  {
    /* Write Log to file */
    charCount += write(filedesOut, sysLogBuff, 1);
    /* Increment Offset*/
    logOffset++;
  }
  close(filedesOut);
  close(fildesSyslog);
  return charCount;
}
/* Clear IDS Log */
extern void IdsClearLog(void)
{
  remove("/home/iwahdan/Ids.log");
}
