#include "libcommon.h"

bool prefix (const char *pre, const char *str, size_t n)
{
	return strncmp (pre, str, n) == 0;
}

char *getBasename (char *filename)
{
	return basename (strdup (filename));
}

char *getHostnameFromFilename (char *filename)
{
	char *pch = strtok (filename, "_");
	pch = strtok (NULL, "_");
	return pch;
}

char *rtrim (const char *s)
{
	while (isspace (*s) || !isprint (*s)) ++s;
	return strdup (s);
}

char *ltrim (const char *s)
{
	char *r = strdup (s);
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

void printUsage ()
{
	fputs (("USAGE\n"), stdout);
	printf ("\t%s [-f filename] [-t audit|job] [-h] [-v]\n", PROGRAM_NAME);
}

void help ()
{
	printUsage ();
	fputs (("\nDESCRIPTION\n"), stdout);
	fputs (("\n\
\tConverts information from IBM iSeries (AS/400) log files to a JSON format that\n\
\tis more understandable and easy to process on most computers and systems.\n"), stdout);
	fputs (("\nOPTIONS\n"), stdout);
	fputs (("\n\
\t-f, --file\tLog file with input data.\n\
\t-t, --type\tType log  data. In  this  version  only the values \"audit\" and\n\
\t\t\t\"job\" are valid.\n\
\t-v, --version\tPrint the program version.\n\
\t-h, --help\tPrint this help.\n"), stdout);
	fputs (("\nLICENSE\n"), stdout);
	fputs (("\n\
\tLicense GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n\
\tThis is free software: you are free to change and redistribute it.\n\
\tThere is NO WARRANTY, to the extent permitted by law.\n"), stdout);
}