#include <stdio.h>
#include <string.h>
#include "auditlogreader.h"

int main(int argc, char *argv[])
{
	if (argc < 2) return 1;

	char *filename = argv[1], *line = NULL, *trim_line = NULL;
	int n_line = 0, n_msgs = 0;
	size_t len = 0;
	ssize_t read;
	FILE *fp;
	bool isPage = false;

	INIT_AUDITLOG(al);

	fp = fopen(filename, "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1)
	{
		trim_line = trim(line);

		// The first five lines are the header. The third line can be excluded.
		if (!isPage && (n_line <= 5) && (n_line != 2))
		{
			processLogHeader(trim_line, &al, n_line);
		}

		// If line starts with al.headerDate is a new page.
		// Set isPage to true and reset n_line to 0 to control page lines.
		if (prefix(trim_line, al.headerDate, HEADER_MAXSTRLEN - 1))
		{
			isPage = true;
			n_line = 0;
			continue;
		}

		// If it's a page, the lines are processed from the fourth.
		if (isPage && (n_line > 3)) processLogPage(trim_line, &al, &n_msgs);

		// Set audit log file name as fileName field in struct.
		strcpy(al.fileName, filename);

		n_line++;
	}

	free(trim_line);
	free(line);
	
	exit(EXIT_SUCCESS);
}