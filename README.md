<p align="center"><img src="https://github.com/JavDomGom/iserieslog2json/blob/main/img/iserieslog2json_logo.png"></p>

## Status

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-brightgreen.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Release](https://img.shields.io/badge/release-v1.0.0-brightgreen)](https://github.com/JavDomGom/iserieslog2json/releases/latest)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/JavDomGom/iserieslog2json)
[![Build Status](https://travis-ci.com/JavDomGom/iserieslog2json.svg?branch=main)](https://travis-ci.com/github/JavDomGom/iserieslog2json)
![Contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg)

## Basic overview

**iserieslog2json** converts information from IBM iSeries (AS/400) log files to a JSON format that is more understandable and easy to process on most computers and systems. In this version it only works with `audit` and `job` logs. In the future, you will be able to work with more types of log files.

## Dependencies

Check has the following dependencies:

- [GCC](https://gcc.gnu.org/install/) (required)
- [GNU Make](https://www.gnu.org/software/make/) (optional, can be compiled manually)
- [Check](https://github.com/libcheck/check) (optional, for testing)
- [Gcovr](https://github.com/gcovr/gcovr) (optional, to generate code coverage reports)
- [Valgrind](https://valgrind.org/docs/manual/quick-start.html) (optional, to detect many memory-related errors)

## Building or install on GNU/Linux

On a GNU/Linux system you can build and install **iserieslog2json** with the usual `sudo make install` procedure.

```bash
~$ sudo make install
```

This way you will have the binary available in `/usr/local/bin/iserieslog2json` to run it from any directory on your computer.

To uninstall:

```bash
~$ sudo make uninstall
```

If you just want to compile the code and get a binary in the current directory you must run `make build` without `sudo`.

```bash
~$ make build
```

The resulting `iserieslog2json` binary file can then be placed and run anywhere on your computer of your choice.

## How to run

```
~$ ./iserieslog2json -h
USAGE
        iserieslog2json [-f filename] [-t audit|job] [-l en|es] [-h] [-v]

DESCRIPTION

        Converts information from IBM iSeries (AS/400) log files to a JSON format that
        is more understandable and easy to process on most computers and systems.

OPTIONS

        -f, --file      Log file with input data.
        -l, --language  Logs language. In  this  version  only the values "en" and "es"
                        are valid.
        -t, --type      Type log  data. In  this  version  only the values "audit" and
                        "job" are valid.
        -v, --version   Print the program version.
        -h, --help      Print this help.

LICENSE

        License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>
        This is free software: you are free to change and redistribute it.
        There is NO WARRANTY, to the extent permitted by law.
```

For example:

```bash
~$ ./iserieslog2json -f AUDIT_HOSTNAME_YYYYMMDD.txt -t audit -l en
```

or

```bash
~$ ./iserieslog2json -f JOB_HOSTNAME_YYYYMMDD.txt -t job -l en
```

### Input data (e.g AUDIT_HOSTNAME_YYYYMMDD.txt file)

```
                                                                           QUERY NAME . . QSECCD
                                                                           LIBRARY NAME . . QSYS
                                                             FILE      LIBRARY  MEMBER    FORMAT
                                                           QASYCDJ4  QTEMP    QASYCDJ4  QASYCDJ4
                                                                     DATE . . . . . . . 14/04/20
                                                                     TIME . . . . . . . 01:03:07
14/04/20  01:03:07                                                                     PAGE    1
  ENTRY  USER       OBJECT   LIBRARY PROG JOB        JOB       JOB    INDICATION
  TYPE   PROFILE    NAME     NAME    CL   NAME       USER      NUMBER HOUR
SERIAL
COMMAND
CD   C   MIMIXOWN   CHKOBJ   QSYS     E   RCV_RUNCMD MIMIXOWN  481053 2020-04-14-00.00.00.045045
CHKOBJ OBJ(MIMIX/H1SPCLVL) OBJTYPE(*DTAARA)
CD   C   MIMIXOWN   CHKOBJ   QSYS     E   RCV_RUNCMD MIMIXOWN  481053 2020-04-14-00.00.00.045637
CHKOBJ OBJ(MIMIX/HTSPCLVL) OBJTYPE(*DTAARA)
CD   C   MIMIXOWN   CALL     QSYS     E   RCV_RUNCMD MIMIXOWN  481053 2020-04-14-00.00.00.104765
CALL PGM(MXTHRUPUT) PARM('SOURCE')
...
...
Several million lines ...
...
...
CD   X   QSECOFR    QSH      QSYS     B   BFI_HW     QSECOFR   481054 2020-04-14-00.00.00.113517
CD   C   QBRMS      PING     QSYS     E   QBRMSYNC   QBRMS     481054 2020-04-14-00.00.00.115229
QSYS/PING RMTSYS(BRMSG5) MSGMODE(*QUIET *ESCAPE) NBRPKT(1)
CD   C   IOPTOWNER  CHGDTARA QSYS     Y   IDDIRPRC   IOPTOWNER 481339 2020-04-14-00.00.00.692237
CD   C   IOPTOWNER  RCLRSC   QSYS     Y   IDDIRPRC   IOPTOWNER 481339 2020-04-14-00.00.00.692317
CD   C   IOPTOWNER  SETAPGRP QSYS     E   IDDIRPRC   IOPTOWNER 481339 2020-04-14-00.00.00.704525
SETASPGRP ASPGRP(*NONE)
CD   C   ADMSSRA1   CHKOBJ   QSYS     E   RMTSYSTEM  CNDINST   481347 2020-04-14-00.00.00.813819
CHKOBJ OBJ(CDUQ886459) OBJTYPE(*USRQ)
CD   C   MDOWNER    DLYJOB   QSYS     Y   MDPUSH1    MDOWNER   481357 2020-04-14-00.00.00.951833
DLYJOB DLY(5)
* * * E N D  O F  R E P O R T * * *
```

### Output data (JSON structure for each event):

```json
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "MIMIXOWN", "objectName": "CHKOBJ", "libraryName": "QSYS", "progCL": "E", "jobName": "RCV_RUNCMD", "jobUser": "MIMIXOWN", "jobNumber": "481053", "dateTime": "2020-04-14-00.00.00.045045", "commandLine": " CHKOBJ OBJ(MIMIX/H1SPCLVL) OBJTYPE(*DTAARA)", "fileName": "AUDIT_HOSTNAME_YYYYMMDD.txt", "serverName": "HOSTNAME"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "MIMIXOWN", "objectName": "CHKOBJ", "libraryName": "QSYS", "progCL": "E", "jobName": "RCV_RUNCMD", "jobUser": "MIMIXOWN", "jobNumber": "481053", "dateTime": "2020-04-14-00.00.00.045637", "commandLine": " CHKOBJ OBJ(MIMIX/HTSPCLVL) OBJTYPE(*DTAARA)", "fileName": "AUDIT_HOSTNAME_YYYYMMDD.txt", "serverName": "HOSTNAME"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "MIMIXOWN", "objectName": "CALL", "libraryName": "QSYS", "progCL": "E", "jobName": "RCV_RUNCMD", "jobUser": "MIMIXOWN", "jobNumber": "481053", "dateTime": "2020-04-14-00.00.00.104765", "commandLine": " CALL PGM(MXTHRUPUT) PARM('SOURCE')", "fileName": "AUDIT_HOSTNAME_YYYYMMDD.txt", "serverName": "HOSTNAME"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "X", "userProfile": "QSECOFR", "objectName": "QSH", "libraryName": "QSYS", "progCL": "B", "jobName": "BFI_HW", "jobUser": "QSECOFR", "jobNumber": "481054", "dateTime": "2020-04-14-00.00.00.113517", "commandLine": "", "fileName": "AUDIT_HOSTNAME_YYYYMMDD.txt", "serverName": "HOSTNAME"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "QBRMS", "objectName": "PING", "libraryName": "QSYS", "progCL": "E", "jobName": "QBRMSYNC", "jobUser": "QBRMS", "jobNumber": "481054", "dateTime": "2020-04-14-00.00.00.115229", "commandLine": " QSYS/PING RMTSYS(BRMSG5) MSGMODE(*QUIET *ESCAPE) NBRPKT(1)", "fileName": "AUDIT_HOSTNAME_YYYYMMDD.txt", "serverName": "HOSTNAME"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "IOPTOWNER", "objectName": "CHGDTARA", "libraryName": "QSYS", "progCL": "Y", "jobName": "IDDIRPRC", "jobUser": "IOPTOWNER", "jobNumber": "481339", "dateTime": "2020-04-14-00.00.00.692237", "commandLine": "", "fileName": "AUDIT_HOSTNAME_YYYYMMDD.txt", "serverName": "HOSTNAME"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "IOPTOWNER", "objectName": "RCLRSC", "libraryName": "QSYS", "progCL": "Y", "jobName": "IDDIRPRC", "jobUser": "IOPTOWNER", "jobNumber": "481339", "dateTime": "2020-04-14-00.00.00.692317", "commandLine": "", "fileName": "AUDIT_HOSTNAME_YYYYMMDD.txt", "serverName": "HOSTNAME"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "IOPTOWNER", "objectName": "SETAPGRP", "libraryName": "QSYS", "progCL": "E", "jobName": "IDDIRPRC", "jobUser": "IOPTOWNER", "jobNumber": "481339", "dateTime": "2020-04-14-00.00.00.704525", "commandLine": " SETASPGRP ASPGRP(*NONE)", "fileName": "AUDIT_HOSTNAME_YYYYMMDD.txt", "serverName": "HOSTNAME"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "ADMSSRA1", "objectName": "CHKOBJ", "libraryName": "QSYS", "progCL": "E", "jobName": "RMTSYSTEM", "jobUser": "CNDINST", "jobNumber": "886460", "dateTime": "2020-10-28-23.59.57.624928", "commandLine": " CHKOBJ OBJ(CDUQ886459) OBJTYPE(*USRQ)", "fileName": "AUDIT_HOSTNAME_YYYYMMDD.txt", "serverName": "HOSTNAME"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "MDOWNER", "objectName": "DLYJOB", "libraryName": "QSYS", "progCL": "Y", "jobName": "MDPUSH1", "jobUser": "MDOWNER", "jobNumber": "674561", "dateTime": "2020-10-28-23.59.59.052944", "commandLine": " DLYJOB DLY(5)", "fileName": "AUDIT_HOSTNAME_YYYYMMDD.txt", "serverName": "HOSTNAME"}
```

Where `serverName` field is substring `HOSTNAME` from `AUDIT_HOSTNAME_YYYYMMDD.txt` file.

## Test

To testing use [Check](https://github.com/libcheck/check), a unit testing framework for C. To run a test suite you can run `make test` as follows:

```bash
~$ make test
```

## Coverage

This program uses [gcovr](https://github.com/gcovr/gcovr) in conjunction with [GCC](https://gcc.gnu.org/) to generate code coverage reports. To install it:

```bash
~$ sudo apt-get update
~$ sudo apt-get install gcovr
```

To generate HTML code coverage reports:

```bash
~$ make coverage_report.html
```

This `make` option will first execute the tests and finally generate the code coverage report in HTML format. You can find it in the current directory as `*.html` files.

## Memory check

The [Valgrind](https://valgrind.org/docs/manual/quick-start.html) tool suite provides a number of debugging and profiling tools that help you make your programs faster and more correct. The most popular of these tools is called Memcheck. It can detect many memory-related errors that are common in C and C++ programs and that can lead to crashes and unpredictable behaviour.

```bash
~$ make valgrind FILE=AUDIT_HOSTNAME_YYYYMMDD.txt TYPE=audit
```

If everything is ok the output is:

```
==27052== All heap blocks were freed -- no leaks are possible
==27052==
==27052== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==27052== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## Questions

If you have questions, please email inquiries to <JavDomGom@protonmail.com>.

If you don't understand the documentation, please tell us, so we can explain it
better. The general idea is: if you need to ask for help, then something needs
to be fixed so you (and others) don't need to ask for help. Asking questions
helps us to know what needs to be documented, described, and/or fixed.
