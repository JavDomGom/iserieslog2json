#ifndef AUDITLOG2JSON_H
#define AUDITLOG2JSON_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define PROGRAM_NAME "auditlog2json"
#define PROGRAM_VERSION "1.0.0"
#define AUTHORS "Javier Dominguez Gomez"

#define CHUNK_SIZE 500
#define LINE_MAX_SIZE 210

#define HEADER_MAXSTRLEN 10
#define HEADER_MAXWORDS 4
#define PAGE_MAXSTRLEN 27
#define PAGE_MAXWORDS 11
#define TYPE_INPUT_MAXSTRLEN 3
#define MODE_MAXSTRLEN 2
#define USER_PROFILE_MAXSTRLEN 10
#define OBJECT_NAME_MAXSTRLEN 15
#define LIBRARY_NAME_MAXSTRLEN 8
#define PROGCL_MAXSTRLEN 2
#define JOB_NAME_MAXSTRLEN 15
#define JOB_USER_MAXSTRLEN 10
#define JOB_NUMBER_MAXSTRLEN 10
#define DATETIME_MAXSTRLEN 30
#define COMMAND_LINE_MAXSTRLEN 1024
#define FILENAME_MAXSTRLEN 128
#define SERVER_NAME_MAXSTRLEN 15

typedef struct
{
	char headerQueryName[HEADER_MAXSTRLEN];
	char headerLibraryName[HEADER_MAXSTRLEN];
	char headerFile[HEADER_MAXSTRLEN];
	char headerLibrary[HEADER_MAXSTRLEN];
	char headerMember[HEADER_MAXSTRLEN];
	char headerFormat[HEADER_MAXSTRLEN];
	char headerDate[HEADER_MAXSTRLEN];
	char headerTime[HEADER_MAXSTRLEN];
	char typeInput[TYPE_INPUT_MAXSTRLEN];
	char mode[MODE_MAXSTRLEN];
	char userProfile[USER_PROFILE_MAXSTRLEN];
	char objectName[OBJECT_NAME_MAXSTRLEN];
	char libraryName[LIBRARY_NAME_MAXSTRLEN];
	char progCL[PROGCL_MAXSTRLEN];
	char jobName[JOB_NAME_MAXSTRLEN];
	char jobUser[JOB_USER_MAXSTRLEN];
	char jobNumber[JOB_NUMBER_MAXSTRLEN];
	char dateTime[DATETIME_MAXSTRLEN];
	char commandLine[COMMAND_LINE_MAXSTRLEN];
	char fileName[FILENAME_MAXSTRLEN];
	char serverName[SERVER_NAME_MAXSTRLEN];
} auditLog;

bool prefix (const char *pre, const char *str, size_t n);
char *rtrim (const char *s);
char *ltrim (const char *s);
char *trim (const char *s);
void processLogHeader (char *line, auditLog *al, int n_line);
void processLogPage (char *line, auditLog *al, int *n_msgs);
void printStructToJSON (auditLog *al);
void printUsage ();
void help ();

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

#endif