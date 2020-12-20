#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auditlogreader.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Must supply a filename to read.\n");
		exit(1);
	}

	char *filename = argv[1];
	int n_line = 0, n_msgs = 0;
	bool isPage = false;

	// Load file into memory data structure using dynamically-sized arrays.
	char **lines = loadfile(filename);

	if (!lines)
	{
		fprintf(stderr, "Can't build data structure.");
		exit(1);
	}

	INIT_AUDITLOG(al);

	// Process the entire file line by line.
	for (int i = 0; lines[i] != NULL; i++)
	{
		// The first five lines are the header. The third line can be excluded.
		if (!isPage && (n_line <= 5) && (n_line != 2))
		{
			processLogHeader(lines[i], &al, n_line);
		}

		// If line starts with "* * *" is the end of log. Not process and continue.
		if (prefix(lines[i], "* * *", 5)) continue;

		// If line starts with al.headerDate is a new page.
		// Set isPage to true and reset n_line to 0 to control page lines.
		if (prefix(lines[i], al.headerDate, HEADER_MAXSTRLEN - 1))
		{
			isPage = true;
			n_line = 0;
			continue;
		}

		char *trim_line = trim(lines[i]);

		// If it's a page, the lines are processed from the fourth n_line.
		if (isPage && (n_line > 3)) processLogPage(trim_line, &al, &n_msgs);

		free(trim_line);

		// Set audit log file name as fileName field in struct.
		strcpy(al.fileName, filename);
		
		n_line++;
	}

	free(*lines);

	exit(EXIT_SUCCESS);
}