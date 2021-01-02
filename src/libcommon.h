#ifndef LIBCOMMON_H
#define LIBCOMMON_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define PROGRAM_NAME "iserieslog2json"
#define PROGRAM_VERSION "1.0.0"
#define AUTHORS "Javier Dominguez Gomez"

bool prefix (const char *pre, const char *str, size_t n);
char *getBasename (char *filename);
char *getHostnameFromFilename (char *filename);
char *rtrim (const char *s);
char *ltrim (const char *s);
char *trim (const char *s);
void printUsage ();
void help ();

#endif  /* LIBCOMMON_H */