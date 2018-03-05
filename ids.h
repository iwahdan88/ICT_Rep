
#ifndef __IDS_SENSOR__
#define __IDS_SENSOR__

/* Callback function to be called by OSAL Layer for logging events from other OCU Components */
extern void IdsReportEvent(void* event);
/* Periodic Function to fetsch Syslog for Events */
extern void IdsAnalyseSysLog(char* syslogpath);

#endif
