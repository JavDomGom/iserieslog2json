#include "libcommon.h"
#include "libjoblog.h"

void jobProcessLogHeader (char *line, jobLog *jl)
{
	char arr[JOB_HEADER_MAXWORDS][JOB_HEADER_MAXSTRLEN + 1] = {0};
	char logDateTime[JOB_HEADER_DATETIME_MAXSTRLEN];
	char *pch, *date, *time, *timeZone;
	int i = 0, k = 0;
	pch = strtok (line, " ");

	while (pch != NULL && k < JOB_HEADER_MAXWORDS)
	{
		if (i >= 4) strncpy (arr[k++], pch, JOB_HEADER_MAXSTRLEN);
		pch = strtok (NULL, " ");
		i++;
	}
	
	date = arr[2];
	time = arr[3];
	timeZone = arr[4];

	snprintf (logDateTime, sizeof logDateTime, "%s %s %s", date, time, timeZone);

	strcpy (jl->user, arr[0]);
	strcpy (jl->jobLogName, arr[1]);
	strcpy (jl->dateTime, logDateTime);
}

void jobProcessPageHeader (char *line, jobLog *jl)
{
	char arr[JOB_PAGE_HEADER_MAXWORDS][JOB_PAGE_HEADER_MAXSTRLEN] = {0};
	char *pch;
	int i = 0;
	pch = strtok (line, " ");

	while (pch != NULL && i < JOB_PAGE_HEADER_MAXWORDS)
	{
		strncpy (arr[i++], pch, JOB_PAGE_HEADER_MAXSTRLEN);
		pch = strtok (NULL, " ");
	}

	strcpy (jl->IBMiOSProgramName, arr[0]);
	strcpy (jl->IBMiOSProgramVersion, arr[1]);
	strcpy (jl->IBMiOSProgramSize, arr[2]);
}

void jobProcessLogPage (char *line, jobLog *jl, int *n_msgs)
{
	// If line doesn't starts with space is the message header.
	if (line[0] != 32)
	{
		// Print last processed message if exist.
		if (*n_msgs > 0) jobPrintStructToJSON (jl);

		// Clean last message if exist.
		strcpy (jl->msg, "");

		jobProcessMsgHeader (line, jl);
		(*n_msgs)++;
	} else if (line[2] == 32) {
		char *trim_line = trim (line);
		strcat (strcat (jl->msg, " "), trim_line);
		free (trim_line);
	}
}

void jobProcessJobAttributes (char *line, jobLog *jl, int n_line)
{
	char arr[JOB_ATTR_MAXWORDS][JOB_ATTR_MAXSTRLEN] = {0};
	char *pch;
	int a_field, b_field, i = 0, k = 0;
	pch = strtok (line, " .:");
	switch (n_line)
	{
	case 2:
		a_field = 3;
		b_field = 7;
		break;
	case 3:
		a_field = 2;
		b_field = 4;
		break;
	}

	while (pch != NULL && k < JOB_ATTR_MAXWORDS)
	{
		if (i == a_field || i == b_field) strncpy (arr[k++], pch, JOB_ATTR_MAXSTRLEN);
		pch = strtok(NULL, " .:");
		i++;
	}

	switch (n_line)
	{
	case 2:
		strcpy (jl->jobName, arr[0]);
		strcpy (jl->jobNumber, arr[1]);
		break;
	case 3:
		strcpy (jl->jobDescription, arr[0]);
		strcpy (jl->jobLibrary, arr[1]);
		break;
	}
}

void jobProcessMsgHeader (char *line, jobLog *jl)
{
	char arr[JOB_MSG_HEADER_MAXWORDS][JOB_MSG_HEADER_MAXSTRLEN + 1] = {0};
	char msgDateTime[JOB_MSG_HEADER_DATETIME_MAXSTRLEN];
	char *pch, *word, *date, *time;
	int k = 0;
	bool isMsgIDNone, isMsgToPGMExt;
	pch = strtok (line, " ");

	while (pch != NULL && k < JOB_MSG_HEADER_MAXWORDS)
	{
		isMsgIDNone = !strcmp (arr[0], "*NONE");
		isMsgToPGMExt = !strcmp (arr[8], "*EXT");

		// When msgID is "*NONE" msgSEV field is empty.
		// When msgToPGM is "*EXT" msgToPGMLibrary field is empty.
		// In both cases it's replaced by the string "n/a".
		if ((isMsgIDNone && k == 2) || (isMsgToPGMExt && k == 9))
		{
			word = "n/a";
		} else {
			word = pch;
			pch = strtok (NULL, " ");
		}

		strncpy (arr[k++], word, JOB_MSG_HEADER_MAXSTRLEN);
	}
	
	date = arr[3];
	time = arr[4];

	snprintf (msgDateTime, sizeof msgDateTime, "%s %s", date, time);

	strcpy (jl->msgID, arr[0]);
	strcpy (jl->msgType, arr[1]);
	strcpy (jl->msgSEV, arr[2]);
	strcpy (jl->msgDatetime, msgDateTime);
	strcpy (jl->msgFromPGM, arr[5]);
	strcpy (jl->msgFromPGMLibrary, arr[6]);
	strcpy (jl->msgFromPGMInst, arr[7]);
	strcpy (jl->msgToPGM, arr[8]);
	strcpy (jl->msgToPGMLibrary, arr[9]);
	strcpy (jl->msgToPGMInst, arr[10]);
}

void jobPrintStructToJSON (jobLog *jl)
{
    printf ("{\"user\": \"%s\", ", jl->user);
    printf ("\"jobLogName\": \"%s\", ", jl->jobLogName);
    printf ("\"dateTime\": \"%s\", ", jl->dateTime);
    printf ("\"IBMiOSProgramName\": \"%s\", ", jl->IBMiOSProgramName);
    printf ("\"IBMiOSProgramVersion\": \"%s\", ", jl->IBMiOSProgramVersion);
    printf ("\"IBMiOSProgramSize\": \"%s\", ", jl->IBMiOSProgramSize);
    printf ("\"jobName\": \"%s\", ", jl->jobName);
    printf ("\"jobNumber\": \"%s\", ", jl->jobNumber);
	printf ("\"jobDescription\": \"%s\", ", jl->jobDescription);
    printf ("\"jobLibrary\": \"%s\", ", jl->jobLibrary);
	printf ("\"msgID\": \"%s\", ", jl->msgID);
	printf ("\"msgType\": \"%s\", ", jl->msgType);
	printf ("\"msgSEV\": \"%s\", ", jl->msgSEV);
	printf ("\"msgDatetime\": \"%s\", ", jl->msgDatetime);
	printf ("\"msgFromPGM\": \"%s\", ", jl->msgFromPGM);
	printf ("\"msgFromPGMLibrary\": \"%s\", ", jl->msgFromPGMLibrary);
	printf ("\"msgFromPGMInst\": \"%s\", ", jl->msgFromPGMInst);
	printf ("\"msgToPGM\": \"%s\", ", jl->msgToPGM);
	printf ("\"msgToPGMLibrary\": \"%s\", ", jl->msgToPGMLibrary);
	printf ("\"msgToPGMInst\": \"%s\", ", jl->msgToPGMInst);
	printf ("\"msg\": \"%s\"}\n", jl->msg);
}

void processJobLog (char *filename)
{
	char *line = NULL;
	int n_line = 0, n_msgs = 0;
	size_t len = 0;
	ssize_t read;
	FILE *fp;
	bool isPage = false;

	INIT_JOBLOG (jl);

	fp = fopen (filename, "r");
	if (fp == NULL) exit (EXIT_FAILURE);

	while ((read = getline (&line, &len, fp)) != -1)
	{
		char *ltrim_line = ltrim (line);

		// If line starts with JOB_PREFIX_LOG_INI_*.
		if (
			prefix (ltrim_line, JOB_PREFIX_LOG_INI_EN, strlen (JOB_PREFIX_LOG_INI_EN)) ||
			prefix (ltrim_line, JOB_PREFIX_LOG_INI_ES, strlen (JOB_PREFIX_LOG_INI_ES))
		)
		{
			jobProcessLogHeader (ltrim_line, &jl);
		}

		// If line starts with JOB_PREFIX_LOG_END_* don't process and continue.
		if (
			prefix (ltrim_line, JOB_PREFIX_LOG_END_EN, strlen (JOB_PREFIX_LOG_END_EN)) ||
			prefix (ltrim_line, JOB_PREFIX_LOG_END_ES, strlen (JOB_PREFIX_LOG_END_ES))
		)
		{
			isPage = false;
			n_line = 0;
			free (ltrim_line);
			continue;
		}

		// If 2th line.
		if (n_line == 1) jobProcessPageHeader (ltrim_line, &jl);

		// If 3th or 4th lines.
		if (n_line == 2 || n_line == 3) jobProcessJobAttributes (ltrim_line, &jl, n_line);

		// If line starts with JOB_PREFIX_MSG_HEADER_* don't process and continue..
		if (
			prefix (ltrim_line, JOB_PREFIX_MSG_HEADER_EN, strlen (JOB_PREFIX_MSG_HEADER_EN)) ||
			prefix (ltrim_line, JOB_PREFIX_MSG_HEADER_ES, strlen (JOB_PREFIX_MSG_HEADER_ES))
		)
		{
			isPage = true;
			n_line++;
			free (ltrim_line);
			continue;
		}

		// If it's a page, the lines are processed from the fifth n_line.
		if (isPage && (n_line > 4)) jobProcessLogPage (ltrim_line, &jl, &n_msgs);

		free (ltrim_line);
		n_line++;
	}
	
	// Print last processed message.
	jobPrintStructToJSON (&jl);

	free (line);
	fclose (fp);
}