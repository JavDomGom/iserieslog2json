#ifndef LIBJOBLOG_H
#define LIBJOBLOG_H

#define JOB_PREFIX_LOG_INI_EN "START"
#define JOB_PREFIX_LOG_INI_ES "INICIO"
#define JOB_PREFIX_LOG_END_EN "END"
#define JOB_PREFIX_LOG_END_ES "FIN"
#define JOB_PREFIX_MSG_HEADER_EN "MSGID"
#define JOB_PREFIX_MSG_HEADER_ES "IDMSJ"
#define JOB_HEADER_MAXSTRLEN 10
#define JOB_HEADER_MAXWORDS 5
#define JOB_HEADER_DATETIME_MAXSTRLEN 29
#define JOB_PAGE_HEADER_MAXSTRLEN 8
#define JOB_PAGE_HEADER_MAXWORDS 3
#define JOB_ATTR_MAXWORDS 2
#define JOB_ATTR_MAXSTRLEN 11
#define JOB_MSG_HEADER_MAXSTRLEN 15
#define JOB_MSG_HEADER_MAXWORDS 11
#define JOB_MSG_HEADER_DATETIME_MAXSTRLEN 26
#define JOB_MSG_MAXSTRLEN 5000

typedef struct
{
	char user[JOB_HEADER_MAXSTRLEN];
	char jobLogName[JOB_HEADER_MAXSTRLEN];
	char dateTime[JOB_HEADER_DATETIME_MAXSTRLEN];
	char IBMiOSProgramName[JOB_PAGE_HEADER_MAXSTRLEN];
	char IBMiOSProgramVersion[JOB_PAGE_HEADER_MAXSTRLEN];
	char IBMiOSProgramSize[JOB_PAGE_HEADER_MAXSTRLEN];
	char jobName[JOB_ATTR_MAXSTRLEN];
	char jobNumber[JOB_ATTR_MAXSTRLEN];
	char jobDescription[JOB_ATTR_MAXSTRLEN];
	char jobLibrary[JOB_ATTR_MAXSTRLEN];
	char msgID[JOB_MSG_HEADER_MAXSTRLEN];
	char msgType[JOB_MSG_HEADER_MAXSTRLEN];
	char msgSEV[JOB_MSG_HEADER_MAXSTRLEN];
	char msgDatetime[JOB_MSG_HEADER_DATETIME_MAXSTRLEN];
	char msgFromPGM[JOB_MSG_HEADER_MAXSTRLEN];
	char msgFromPGMLibrary[JOB_MSG_HEADER_MAXSTRLEN];
	char msgFromPGMInst[JOB_MSG_HEADER_MAXSTRLEN];
	char msgToPGM[JOB_MSG_HEADER_MAXSTRLEN];
	char msgToPGMLibrary[JOB_MSG_HEADER_MAXSTRLEN];
	char msgToPGMInst[JOB_MSG_HEADER_MAXSTRLEN];
	char msg[JOB_MSG_MAXSTRLEN];
} jobLog;

void jobProcessLogHeader (char *line, jobLog *jl);
void jobProcessPageHeader (char *line, jobLog *jl);
void jobProcessLogPage (char *line, jobLog *jl, int *n_msgs);
void jobProcessJobAttributes (char *line, jobLog *jl, int n_line);
void jobProcessMsgHeader (char *line, jobLog *jl);
void jobPrintStructToJSON (jobLog *jl);
void processJobLog (char *filename);

#define INIT_JOBLOG(X) jobLog X = { \
	.user = "", \
	.jobLogName = "", \
	.dateTime = "", \
	.IBMiOSProgramName = "", \
	.IBMiOSProgramVersion = "", \
	.IBMiOSProgramSize = "", \
	.jobName = "", \
	.jobNumber = "", \
	.jobDescription = "", \
	.jobLibrary = "", \
	.msgID = "", \
	.msgType = "", \
	.msgSEV = "", \
	.msgDatetime = "", \
	.msgFromPGM = "", \
	.msgFromPGMLibrary = "", \
	.msgFromPGMInst = "", \
	.msgToPGM = "", \
	.msgToPGMLibrary = "", \
	.msgToPGMInst = "", \
	.msg = "" \
}

#endif  /* LIBJOBLOG_H */