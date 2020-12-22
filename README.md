# AS400 auditlog2json

Convert AS400 audit logs to JSON format.

## How to compile

```bash
~$ make build
```

## How to run

```bash
~$ ./auditlog2json -f AUDIT_LOG_FILE.txt
```

Output (JSON structure for each event):

```json
{
  "headerQueryName": "XXXXXX",
  "headerLibraryName": "XXXX",
  "headerFile": "XXXXXXXX",
  "headerLibrary": "XXXXX",
  "headerMember": "XXXXXXXX",
  "headerFormat": "XXXXXXXX",
  "headerDate": "DD/MM/YY",
  "headerTime": "hh:mm:ss",
  "typeInput": "XX",
  "mode": "X",
  "userProfile": "XXXXXXXXX",
  "objectName": "XXXXXX",
  "libraryName": "XXXX",
  "progCL": "X",
  "jobName": "XXXXXXXX",
  "jobUser": "XXXXXXXXX",
  "jobNumber": "000001",
  "dateTime": "YYYY-MM-DD-00.00.00.000000",
  "commandLine": "XXXXXXXXXXXXXXXXXXXXX...",
  "fileName": "AUDIT_LOG_FILE.txt",
  "serverName": "XXXXXXXX"
}
```
