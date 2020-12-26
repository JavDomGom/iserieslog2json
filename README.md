<p align="center"><img src="https://github.com/JavierDominguezGomez/AS400_auditlog2json/blob/main/img/AS400_auditlog2json_logo.png"></p>

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-brightgreen.svg)](https://www.gnu.org/licenses/gpl-3.0)
![GitHub top language](https://img.shields.io/github/languages/top/JavierDominguezGomez/AS400_auditlog2json)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/JavierDominguezGomez/AS400_auditlog2json)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/JavierDominguezGomez/AS400_auditlog2json.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/JavierDominguezGomez/AS400_auditlog2json/context:cpp)
[![Build Status](https://travis-ci.org/JavierDominguezGomez/AS400_auditlog2json.svg?branch=main)](https://travis-ci.org/JavierDominguezGomez/AS400_auditlog2json)
![Contributions welcome](https://img.shields.io/badge/contributions-welcome-yellow.svg)

## Basic Overview

The auditlog2json tool converts information from IBM iSeries audit report log files on an AS400 system to a JSON format that is much more understandable and easy to process on most computers and systems.

## How to compile

```bash
~$ make build
```

## Memory check

```bash
~$ make valgrind FILE=audit.log
```

## How to run

```bash
~$ ./auditlog2json -f audit.log
```

### Input data (audit.log file)

```
                                                                           QUERY NAME . . QSECCD
                                                                           LIBRARY NAME  . .QSYS
                                                             FILE      LIBRARY  MEMBER    FORMAT
                                                           QASYCDJ4  QTEMP    QASYCDJ4  QASYCDJ4
                                                                     DATE . . . . . . . 14/04/20
                                                                     TIME . . . . . . . 01:03:07
14/04/20  01:03:07                                                                     PAGE    1
  ENTRY  USER       OBJECT   LIBRARY PROG JOB        JOB       JOB    INDICATION
  TYPE   PROFILE    NAME     NAME    CL   NAME       USER      NUMBER HOUR
SERIE
MANDATO
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
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "MIMIXOWN", "objectName": "CHKOBJ", "libraryName": "QSYS", "progCL": "E", "jobName": "RCV_RUNCMD", "jobUser": "MIMIXOWN", "jobNumber": "481053", "dateTime": "2020-04-14-00.00.00.045045", "commandLine": " CHKOBJ OBJ(MIMIX/H1SPCLVL) OBJTYPE(*DTAARA)", "fileName": "audit.log", "serverName": "jdghost"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "MIMIXOWN", "objectName": "CHKOBJ", "libraryName": "QSYS", "progCL": "E", "jobName": "RCV_RUNCMD", "jobUser": "MIMIXOWN", "jobNumber": "481053", "dateTime": "2020-04-14-00.00.00.045637", "commandLine": " CHKOBJ OBJ(MIMIX/HTSPCLVL) OBJTYPE(*DTAARA)", "fileName": "audit.log", "serverName": "jdghost"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "MIMIXOWN", "objectName": "CALL", "libraryName": "QSYS", "progCL": "E", "jobName": "RCV_RUNCMD", "jobUser": "MIMIXOWN", "jobNumber": "481053", "dateTime": "2020-04-14-00.00.00.104765", "commandLine": " CALL PGM(MXTHRUPUT) PARM('SOURCE')", "fileName": "audit.log", "serverName": "jdghost"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "X", "userProfile": "QSECOFR", "objectName": "QSH", "libraryName": "QSYS", "progCL": "B", "jobName": "BFI_HW", "jobUser": "QSECOFR", "jobNumber": "481054", "dateTime": "2020-04-14-00.00.00.113517", "commandLine": "", "fileName": "audit.log", "serverName": "jdghost"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "QBRMS", "objectName": "PING", "libraryName": "QSYS", "progCL": "E", "jobName": "QBRMSYNC", "jobUser": "QBRMS", "jobNumber": "481054", "dateTime": "2020-04-14-00.00.00.115229", "commandLine": " QSYS/PING RMTSYS(BRMSG5) MSGMODE(*QUIET *ESCAPE) NBRPKT(1)", "fileName": "audit.log", "serverName": "jdghost"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "IOPTOWNER", "objectName": "CHGDTARA", "libraryName": "QSYS", "progCL": "Y", "jobName": "IDDIRPRC", "jobUser": "IOPTOWNER", "jobNumber": "481339", "dateTime": "2020-04-14-00.00.00.692237", "commandLine": "", "fileName": "audit.log", "serverName": "jdghost"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "IOPTOWNER", "objectName": "RCLRSC", "libraryName": "QSYS", "progCL": "Y", "jobName": "IDDIRPRC", "jobUser": "IOPTOWNER", "jobNumber": "481339", "dateTime": "2020-04-14-00.00.00.692317", "commandLine": "", "fileName": "audit.log", "serverName": "jdghost"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "IOPTOWNER", "objectName": "SETAPGRP", "libraryName": "QSYS", "progCL": "E", "jobName": "IDDIRPRC", "jobUser": "IOPTOWNER", "jobNumber": "481339", "dateTime": "2020-04-14-00.00.00.704525", "commandLine": " SETASPGRP ASPGRP(*NONE)", "fileName": "audit.log", "serverName": "jdghost"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "ADMSSRA1", "objectName": "CHKOBJ", "libraryName": "QSYS", "progCL": "E", "jobName": "RMTSYSTEM", "jobUser": "CNDINST", "jobNumber": "886460", "dateTime": "2020-10-28-23.59.57.624928", "commandLine": " CHKOBJ OBJ(CDUQ886459) OBJTYPE(*USRQ)", "fileName": "audit.log", "serverName": "jdghost"}
{"headerQueryName": "QSECCD", "headerLibraryName": "QSYS", "headerFile": "QASYCDJ4", "headerLibrary": "QTEMP", "headerMember": "QASYCDJ4", "headerFormat": "QASYCDJ4", "headerDate": "14/04/20", "headerTime": "01:03:07", "typeInput": "CD", "mode": "C", "userProfile": "MDOWNER", "objectName": "DLYJOB", "libraryName": "QSYS", "progCL": "Y", "jobName": "MDPUSH1", "jobUser": "MDOWNER", "jobNumber": "674561", "dateTime": "2020-10-28-23.59.59.052944", "commandLine": " DLYJOB DLY(5)", "fileName": "audit.log", "serverName": "jdghost"}
```
