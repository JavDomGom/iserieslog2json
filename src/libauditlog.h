#ifndef LIBAUDITLOG_H
#define LIBAUDITLOG_H

#define AUDIT_HEADER_MAXSTRLEN 10
#define AUDIT_HEADER_MAXWORDS 4
#define AUDIT_PAGE_MAXSTRLEN 27
#define AUDIT_PAGE_MAXWORDS 11
#define AUDIT_TYPE_INPUT_MAXSTRLEN 3
#define AUDIT_MODE_MAXSTRLEN 2
#define AUDIT_USER_PROFILE_MAXSTRLEN 10
#define AUDIT_OBJECT_NAME_MAXSTRLEN 15
#define AUDIT_LIBRARY_NAME_MAXSTRLEN 8
#define AUDIT_PROGCL_MAXSTRLEN 2
#define AUDIT_JOB_NAME_MAXSTRLEN 15
#define AUDIT_JOB_USER_MAXSTRLEN 10
#define AUDIT_JOB_NUMBER_MAXSTRLEN 10
#define AUDIT_DATETIME_MAXSTRLEN 30
#define AUDIT_COMMAND_LINE_MAXSTRLEN 1024
#define AUDIT_FILENAME_MAXSTRLEN 128
#define AUDIT_FILENAME_SUBSTR 3
#define AUDIT_FILENAME_SUBSTR_MAXSTRLEN 8
#define AUDIT_SERVER_NAME_MAXSTRLEN 15

typedef struct
{
	char headerQueryName[AUDIT_HEADER_MAXSTRLEN];
	char headerLibraryName[AUDIT_HEADER_MAXSTRLEN];
	char headerFile[AUDIT_HEADER_MAXSTRLEN];
	char headerLibrary[AUDIT_HEADER_MAXSTRLEN];
	char headerMember[AUDIT_HEADER_MAXSTRLEN];
	char headerFormat[AUDIT_HEADER_MAXSTRLEN];
	char headerDate[AUDIT_HEADER_MAXSTRLEN];
	char headerTime[AUDIT_HEADER_MAXSTRLEN];
	char typeInput[AUDIT_TYPE_INPUT_MAXSTRLEN];
	char mode[AUDIT_MODE_MAXSTRLEN];
	char userProfile[AUDIT_USER_PROFILE_MAXSTRLEN];
	char objectName[AUDIT_OBJECT_NAME_MAXSTRLEN];
	char libraryName[AUDIT_LIBRARY_NAME_MAXSTRLEN];
	char progCL[AUDIT_PROGCL_MAXSTRLEN];
	char jobName[AUDIT_JOB_NAME_MAXSTRLEN];
	char jobUser[AUDIT_JOB_USER_MAXSTRLEN];
	char jobNumber[AUDIT_JOB_NUMBER_MAXSTRLEN];
	char dateTime[AUDIT_DATETIME_MAXSTRLEN];
	char commandLine[AUDIT_COMMAND_LINE_MAXSTRLEN];
	char fileName[AUDIT_FILENAME_MAXSTRLEN];
	char serverName[AUDIT_SERVER_NAME_MAXSTRLEN];
} auditLog;

void auditProcessLogHeader (char *line, auditLog *al, int n_line);
void auditProcessLogPage (char *line, auditLog *al, int *n_msgs);
void auditPrintStructToJSON (auditLog *al);
void processAuditLog (char *filename);

#define INIT_AUDITLOG(X) auditLog X = { \
	.headerQueryName = "", \
	.headerLibraryName = "", \
	.headerFile = "", \
	.headerLibrary = "", \
	.headerMember = "", \
	.headerFormat = "", \
	.headerDate = "", \
	.headerTime = "", \
	.typeInput = "", \
	.mode = "", \
	.userProfile = "", \
	.objectName = "", \
	.libraryName = "", \
	.progCL = "", \
	.jobName = "", \
	.jobUser = "", \
	.jobNumber = "", \
	.dateTime = "", \
	.commandLine = "", \
	.fileName = "", \
	.serverName = "" \
}

#endif  /* LIBAUDITLOG_H */