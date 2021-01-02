#include <unistd.h>
#include <getopt.h>
#include "libcommon.h"

int main (int argc, char *argv[])
{
	int opt;
	char *filename = "", *type = "";

	while (1)
	{
		static struct option long_options[] =
		{
			{"file", required_argument, 0, 'f'},
			{"type", required_argument, 0, 't'},
			{"help", no_argument, 0, 'h'},
			{"version", no_argument, 0, 'v'}
		};

		/* getopt_long stores the option index here. */
		int option_index = 0;

		opt = getopt_long (argc, argv, "f:t:hv", long_options, &option_index);

		/* Detect the end of the options. */
		if (opt == -1) break;

		switch (opt)
		{
			case 'v':
				printf ("%s v%s\n", PROGRAM_NAME, PROGRAM_VERSION);
				exit (EXIT_SUCCESS);
			case 'h':
				help ();
				exit (EXIT_SUCCESS);
			case 'f':
				filename = optarg;
				break;
			case 't':
				type = optarg;
				break;
			case '?':
				if ((optopt == 'f') && (optopt == 't')) printUsage ();
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

	if (!*filename || !*type)
	{
		if (!*filename) printf ("Option -f, --file is mandatory!\n");
		if (!*type) printf ("Option -t, --type is mandatory!\n");
		printUsage ();
		exit (EXIT_FAILURE);
	}

	if (!strcmp (type, "audit")) 
	{
		#include "libauditlog.h"
		processAuditLog (filename);
	} 
	else if (!strcmp (type, "job"))
	{
		#include "libjoblog.h"
		processJobLog (filename);
	}
	else
	{
		printUsage ();
		exit (EXIT_FAILURE);
	}

	exit (EXIT_SUCCESS);
}