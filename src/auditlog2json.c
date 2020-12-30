#include "../src/auditlog2json.h"

bool prefix (const char *pre, const char *str, size_t n)
{
	return strncmp (pre, str, n) == 0;
}

char *rtrim (const char *s)
{
	while (isspace (*s) || !isprint (*s)) ++s;
	return strdup (s);
}

char *ltrim (const char *s)
{
	char *r = strdup(s);
	if (r != NULL)
	{
		char *fr = r + strlen (s) - 1;
		while ((isspace (*fr) || !isprint (*fr) || *fr == 0) && fr >= r) --fr;
		*++fr = 0;
	}
	return r;
}

char *trim (const char *s)
{
	char *r = rtrim (s);
	char *f = ltrim (r);
	free (r);
	return f;
}

void processLogHeader (char *line, auditLog *al, int n_line)
{
	char arr[HEADER_MAXWORDS][HEADER_MAXSTRLEN] = {0};
	char *pch;
	int i = 0, k = 0;
	pch = strtok (line, " .");

	while (pch != NULL && k < HEADER_MAXWORDS)
	{
		strncpy (arr[k++], pch, HEADER_MAXSTRLEN);
		pch = strtok (NULL, " .");
		i++;
	}

	switch (n_line)
	{
	case 0:
		strcpy (al->headerQueryName, arr[2]);
		break;
	case 1:
		strcpy (al->headerLibraryName, arr[2]);
		break;
	case 3:
		strcpy (al->headerFile, arr[0]);
		strcpy (al->headerLibrary, arr[1]);
		strcpy (al->headerMember, arr[2]);
		strcpy (al->headerFormat, arr[3]);
		break;
	case 4:
		strcpy (al->headerDate, arr[1]);
		break;
	case 5:
		strcpy (al->headerTime, arr[1]);
		break;
	}
}

void processLogPage (char *line, auditLog *al, int *n_msgs)
{
	char *lastWord = strrchr (line, ' ');
	struct tm tm;

	memset (&tm, 0, sizeof (struct tm));

	// If lastWord is not null and last word in line is valid formated datetime.
	if (lastWord && strptime (lastWord + 1, "%Y-%m-%d-%H.%M.%S", &tm))
	{
		// Print last processed message if exist.
		if (*n_msgs > 0) printStructToJSON (al);

		// Clean last commandLine if exist.
		strcpy (al->commandLine, "");

		char arr[PAGE_MAXWORDS][PAGE_MAXSTRLEN] = {0};
		char *pch;
		int i = 0, k = 0;
		pch = strtok (line, " ");

		while (pch != NULL && k < PAGE_MAXWORDS)
		{
			strncpy (arr[k++], pch, PAGE_MAXSTRLEN);
			pch = strtok (NULL, " ");
			i++;
		}

		strcpy (al->typeInput, arr[0]);
		strcpy (al->mode, arr[1]);
		strcpy (al->userProfile, arr[2]);
		strcpy (al->objectName, arr[3]);
		strcpy (al->libraryName, arr[4]);
		strcpy (al->progCL, arr[5]);
		strcpy (al->jobName, arr[6]);
		strcpy (al->jobUser, arr[7]);
		strcpy (al->jobNumber, arr[8]);
		strcpy (al->dateTime, arr[9]);
		
		(*n_msgs)++;
	}
	else
	{
		strcat (strcat (al->commandLine, " "), line);
	}
}

void printStructToJSON (auditLog *al)
{
	printf ("{\"headerQueryName\": \"%s\", ", al->headerQueryName);
	printf ("\"headerLibraryName\": \"%s\", ", al->headerLibraryName);
	printf ("\"headerFile\": \"%s\", ", al->headerFile);
	printf ("\"headerLibrary\": \"%s\", ", al->headerLibrary);
	printf ("\"headerMember\": \"%s\", ", al->headerMember);
	printf ("\"headerFormat\": \"%s\", ", al->headerFormat);
	printf ("\"headerDate\": \"%s\", ", al->headerDate);
	printf ("\"headerTime\": \"%s\", ", al->headerTime);
	printf ("\"typeInput\": \"%s\", ", al->typeInput);
	printf ("\"mode\": \"%s\", ", al->mode);
	printf ("\"userProfile\": \"%s\", ", al->userProfile);
	printf ("\"objectName\": \"%s\", ", al->objectName);
	printf ("\"libraryName\": \"%s\", ", al->libraryName);
	printf ("\"progCL\": \"%s\", ", al->progCL);
	printf ("\"jobName\": \"%s\", ", al->jobName);
	printf ("\"jobUser\": \"%s\", ", al->jobUser);
	printf ("\"jobNumber\": \"%s\", ", al->jobNumber);
	printf ("\"dateTime\": \"%s\", ", al->dateTime);
	printf ("\"commandLine\": \"%s\", ", al->commandLine);
	printf ("\"fileName\": \"%s\", ", al->fileName);
	printf ("\"serverName\": \"%s\"}\n", al->serverName);
}

void printUsage ()
{
	fputs (("USAGE\n"), stdout);
	printf ("\t%s -f filename | [ -h | -v ]\n", PROGRAM_NAME);
}

void help ()
{
	printUsage ();
	fputs (("\nDESCRIPTION\n"), stdout);
	fputs (("\n\
\tConverts information  from IBM  iSeries  audit  report  log files  on an AS400\n\
\tsystem to a JSON  format that is much more  understandable and easy to process\n\
\ton most computers and systems.\n"), stdout);
	fputs (("\nOPTIONS\n"), stdout);
	fputs (("\n\
\t-f, --file\tFile input with audit log data.\n\
\t-v, --version\tPrint the program version.\n\
\t-h, --help\tPrint this help.\n"), stdout);
	fputs (("\nLICENSE\n"), stdout);
	fputs (("\n\
\tLicense GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n\
\tThis is free software: you are free to change and redistribute it.\n\
\tThere is NO WARRANTY, to the extent permitted by law.\n"), stdout);
}