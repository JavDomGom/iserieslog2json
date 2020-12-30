#include <unistd.h>
#include <getopt.h>
#include "auditlog2json.h"

int main (int argc, char *argv[])
{
	char *filename = argv[1], *line = NULL;
	int n_line = 0, n_msgs = 0, opt;
	size_t len = 0;
	ssize_t read;
	FILE *fp;
	bool isPage = false;

	while (1)
	{
		static struct option long_options[] =
		{
			{"file", required_argument, 0, 'f'},
			{"help", no_argument, 0, 'h'},
			{"version", no_argument, 0, 'v'}
		};

		/* getopt_long stores the option index here. */
		int option_index = 0;

		opt = getopt_long (argc, argv, "f:hv", long_options, &option_index);

		/* Detect the end of the options. */
		if (opt == -1) break;

		switch (opt)
		{
			case 'v':
				printf ("%s v%s\n", PROGRAM_NAME, PROGRAM_VERSION);
				break;
			case 'h':
				help ();
				break;
			case 'f':
				filename = optarg;
				break;
			case '?':
				if (optopt == 'f') printUsage ();
				else if (isprint (optopt)) fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				exit (EXIT_FAILURE);
			default:
				abort ();
		}
	}

	if (optind < argc)
	{
		printf ("non-option ARGV-elements: ");
		while (optind < argc) printf ("%s", argv[optind++]);
		putchar ('\n');
		printUsage ();
		exit (EXIT_FAILURE);
	}

	INIT_AUDITLOG (al);

	fp = fopen (filename, "r");
	if (fp == NULL) exit (EXIT_FAILURE);

	// Set audit log file name as fileName field in auditLog struct.
	strcpy (al.fileName, filename);

	// Set host name as serverName field in auditLog struct.
	gethostname (al.serverName, SERVER_NAME_MAXSTRLEN);

	while ((read = getline (&line, &len, fp)) != -1)
	{
		char *trim_line = trim (line);

		// The first six lines are the header. The third line can be excluded.
		if (!isPage && (n_line <= 5) && (n_line != 2)) processLogHeader (trim_line, &al, n_line);

		// If trim_line starts with "* * *" is the end of log.
		// Print last processed message and break for loop.
		if (prefix (trim_line, "* * *", 5))
		{
			printStructToJSON (&al);
			free (trim_line);
			break;
		}

		// If trim_line starts with al.headerDate is a new page.
		// Set isPage to true and reset n_line to 0 to control page lines.
		if (prefix (trim_line, al.headerDate, HEADER_MAXSTRLEN - 2))
		{
			isPage = true;
			n_line = 0;
			free (trim_line);
			continue;
		}

		// If it's a page, the lines are processed from the fourth n_line.
		if (isPage && (n_line > 3)) processLogPage (trim_line, &al, &n_msgs);

		free (trim_line);
		n_line++;
	}

	fclose (fp);
	free (line);

	exit (EXIT_SUCCESS);
}