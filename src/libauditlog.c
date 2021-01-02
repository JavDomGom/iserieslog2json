#include "libcommon.h"
#include "libauditlog.h"

void auditProcessLogHeader (char *line, auditLog *al, int n_line)
{
	char arr[AUDIT_HEADER_MAXWORDS][AUDIT_HEADER_MAXSTRLEN] = {0};
	char *pch;
	int i = 0, k = 0;
	pch = strtok (line, " .");

	while (pch != NULL && k < AUDIT_HEADER_MAXWORDS)
	{
		strncpy (arr[k++], pch, AUDIT_HEADER_MAXSTRLEN);
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

void auditProcessLogPage (char *line, auditLog *al, int *n_msgs)
{
	char *lastWord = strrchr (line, ' ');
	struct tm tm;

	memset (&tm, 0, sizeof (struct tm));

	// If lastWord is not null and last word in line is valid formated datetime.
	if (lastWord && strptime (lastWord + 1, "%Y-%m-%d-%H.%M.%S", &tm))
	{
		// Print last processed message if exist.
		if (*n_msgs > 0) auditPrintStructToJSON (al);

		// Clean last commandLine if exist.
		strcpy (al->commandLine, "");

		char arr[AUDIT_PAGE_MAXWORDS][AUDIT_PAGE_MAXSTRLEN] = {0};
		char *pch;
		int i = 0, k = 0;
		pch = strtok (line, " ");

		while (pch != NULL && k < AUDIT_PAGE_MAXWORDS)
		{
			strncpy (arr[k++], pch, AUDIT_PAGE_MAXSTRLEN);
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

void auditPrintStructToJSON (auditLog *al)
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

void processAuditLog (char *filename)
{
	char *bname, *line = NULL;
	int n_line = 0, n_msgs = 0;
	size_t len = 0;
	ssize_t read;
	FILE *fp;
	bool isPage = false;

	INIT_AUDITLOG (al);

	fp = fopen (filename, "r");
	if (fp == NULL) exit (EXIT_FAILURE);

	bname = getBasename (filename);

	// Set audit log file name as fileName field in auditLog struct.
	strcpy (al.fileName, bname);

	// Set second substring splitted by "_" from filename as serverName field in auditLog struct.
	strcpy (al.serverName, getHostnameFromFilename (bname));

	while ((read = getline (&line, &len, fp)) != -1)
	{
		char *trim_line = trim (line);

		// The first six lines are the header. The third line can be excluded.
		if (!isPage && (n_line <= 5) && (n_line != 2)) auditProcessLogHeader (trim_line, &al, n_line);

		// If trim_line starts with "* * *" is the end of log.
		// Print last processed message and break loop.
		if (prefix (trim_line, "* * *", 5))
		{
			auditPrintStructToJSON (&al);
			free (trim_line);
			break;
		}

		// If trim_line starts with al.headerDate is a new page.
		// Set isPage to true and reset n_line to 0 to control page lines.
		if (prefix (trim_line, al.headerDate, AUDIT_HEADER_MAXSTRLEN - 2))
		{
			isPage = true;
			n_line = 0;
			free (trim_line);
			continue;
		}

		// If it's a page, the lines are processed from the fourth n_line.
		if (isPage && (n_line > 3)) auditProcessLogPage (trim_line, &al, &n_msgs);

		free (trim_line);
		n_line++;
	}

	free (line);
	free (bname);
	fclose (fp);
}