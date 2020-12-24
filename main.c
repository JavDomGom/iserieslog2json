#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "auditlog2json.h"

int main(int argc, char *argv[])
{
	char *filename = argv[1], *line = NULL;
	int n_line = 0, n_msgs = 0, opt;
	size_t len = 0;
	ssize_t read;
	FILE *fp;
	bool isPage = false;

	while ((opt = getopt(argc, argv, "f:")) != -1) {
		switch (opt) {
			case 'f':
				filename = optarg;
				break;
			case '?':
				if (optopt == 'f')
					printUsage(argv[0]);
				else if (isprint(optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				exit(EXIT_FAILURE);
			default:
				abort();
		}
	}

	if (argc < 3)
	{
		printUsage(argv[0]);
		exit(EXIT_FAILURE);
	}

	INIT_AUDITLOG(al);

	fp = fopen(filename, "r");
	if (fp == NULL) exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1)
	{
		char *trim_line = trim(line);

		// The first five lines are the header. The third line can be excluded.
		if (!isPage && (n_line <= 5) && (n_line != 2))
		{
			processLogHeader(trim_line, &al, n_line);
		}

		// If trim_line starts with "* * *" is the end of log.
		// Print last processed message and break for loop.
		if (prefix(trim_line, "* * *", 5))
		{
			printStructToJSON(&al);
			free(trim_line);
			break;
		}

		// If trim_line starts with al.headerDate is a new page.
		// Set isPage to true and reset n_line to 0 to control page lines.
		if (prefix(trim_line, al.headerDate, HEADER_MAXSTRLEN - 2))
		{
			isPage = true;
			n_line = 0;
			free(trim_line);
			continue;
		}

		// If it's a page, the lines are processed from the fourth n_line.
		if (isPage && (n_line > 3))
		{
			processLogPage(trim_line, &al, &n_msgs);
		}

		free(trim_line);

		// Set audit log file name as fileName field in auditLog struct.
		strcpy(al.fileName, filename);

		// Set host name as serverName field in auditLog struct.
		gethostname(al.serverName, SERVER_NAME_MAXSTRLEN);
		
		n_line++;
	}

	free(line);

	exit(EXIT_SUCCESS);
}