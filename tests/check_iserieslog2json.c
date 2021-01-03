#include <check.h>
#include <unistd.h>
#include "../src/libcommon.h"
#include "../src/libauditlog.h"
#include "../src/libjoblog.h"

INIT_AUDITLOG (al);

START_TEST (test_audit_filename_and_hostname_struct_fields)
{
	char *filename = "AUDIT_HOSTNAME_YYYYMMDD.txt";

	// Set audit log file name as fileName field in auditLog struct.
	strcpy (al.fileName, filename);
	ck_assert_str_eq (al.fileName, filename);

	// Set second substring splitted by "_" from filename as serverName field in auditLog struct.
	char *hostname = getHostnameFromFilename (trim (filename));
	strcpy (al.serverName, hostname);
	ck_assert_str_eq (al.serverName, hostname);
} END_TEST

START_TEST (test_auditProcessLogHeader)
{
	char *trim_line = NULL;
	
	trim_line = trim ("     QUERY NAME . . QSECCD");
	auditProcessLogHeader (trim_line, &al, 0);
	ck_assert_str_eq (al.headerQueryName, "QSECCD");
	
	trim_line = trim ("     LIBRARY NAME . . QSYS");
	auditProcessLogHeader (trim_line, &al, 1);
	ck_assert_str_eq (al.headerLibraryName, "QSYS");

	trim_line = trim ("     QASYCDJ4  QTEMP    QASYCDJ4  QASYCDJ4");
	auditProcessLogHeader (trim_line, &al, 3);
	ck_assert_str_eq (al.headerFile, "QASYCDJ4");
	ck_assert_str_eq (al.headerLibrary, "QTEMP");
	ck_assert_str_eq (al.headerMember, "QASYCDJ4");
	ck_assert_str_eq (al.headerFormat, "QASYCDJ4");
	
	trim_line = trim ("     DATE . . . . . . . 14/04/20");
	auditProcessLogHeader (trim_line, &al, 4);
	ck_assert_str_eq (al.headerDate, "14/04/20");

	trim_line = trim ("     TIME . . . . . . . 01:03:07");
	auditProcessLogHeader (trim_line, &al, 5);
	ck_assert_str_eq (al.headerTime, "01:03:07");

	free (trim_line);
} END_TEST

START_TEST (test_auditProcessLogPage)
{
	char *trim_line = NULL;
	int n_msgs = 0;
	trim_line = trim ("CD   C   MIMIXOWN   CHKOBJ   QSYS     E   RCV_RUNCMD MIMIXOWN  481053 2020-04-14-00.00.00.045045");
	
	auditProcessLogPage (trim_line, &al, &n_msgs);

	ck_assert_str_eq (al.typeInput, "CD");
	ck_assert_str_eq (al.mode, "C");
	ck_assert_str_eq (al.userProfile, "MIMIXOWN");
	ck_assert_str_eq (al.objectName, "CHKOBJ");
	ck_assert_str_eq (al.libraryName, "QSYS");
	ck_assert_str_eq (al.progCL, "E");
	ck_assert_str_eq (al.jobName, "RCV_RUNCMD");
	ck_assert_str_eq (al.jobUser, "MIMIXOWN");
	ck_assert_str_eq (al.jobNumber, "481053");
	ck_assert_str_eq (al.dateTime, "2020-04-14-00.00.00.045045");

	free (trim_line);
} END_TEST

INIT_JOBLOG (jl);

START_TEST (test_jobProcessLogHeader)
{
	char *trim_line = NULL;

	trim_line = trim ("START LOG FOR USER MYUSER   ISERIES1 14/04/20 01:55:30 UTC-04:00S ");
	jobProcessLogHeader (trim_line, &jl);
	ck_assert_str_eq (jl.user, "MYUSER");
	ck_assert_str_eq (jl.jobLogName, "ISERIES1");
	ck_assert_str_eq (jl.dateTime, "14/04/20 01:55:30 UTC-04:00S");

	free (trim_line);
} END_TEST

START_TEST (test_jobProcessPageHeader)
{
	char *trim_line = NULL;

	trim_line = trim (" 5761SS1 V6R1M0 080215   Job Log   ISERIES1 14/04/20 11:50:41 UTC-00:00S   Page   1");
	jobProcessPageHeader (trim_line, &jl);
	ck_assert_str_eq (jl.IBMiOSProgramName, "5761SS1");
	ck_assert_str_eq (jl.IBMiOSProgramVersion, "V6R1M0");
	ck_assert_str_eq (jl.IBMiOSProgramSize, "080215");

	free (trim_line);
} END_TEST

START_TEST (test_jobProcessLogPage)
{
	char *line = NULL;

	line = "   Message . . . . :   ABCDEFGHIJKLMN ";
	jobProcessLogPage (line, &jl, 0);
	ck_assert_str_eq (jl.msg, " Message . . . . :   ABCDEFGHIJKLMN");
} END_TEST

START_TEST (test_jobProcessJobAttributes)
{
	char *ltrim_line = NULL;

	ltrim_line = trim ("  Job name  . . . . . : QPADEV0006  User . . . . . : MYUSER  Number . . . . . . . . . . . : 123456   ");
	jobProcessJobAttributes (ltrim_line, &jl, 2, "en");

	ck_assert_str_eq (jl.jobName, "QPADEV0006");
	ck_assert_str_eq (jl.jobNumber, "123456");

	ltrim_line = trim ("  Nombre de trabajo  . . . . . :   QPADEV0006  Usuario . . . . . . : XE45930  N�mero . . . . . . . . . . . :   123456   ");
	jobProcessJobAttributes (ltrim_line, &jl, 2, "es");

	ck_assert_str_eq (jl.jobName, "QPADEV0006");
	ck_assert_str_eq (jl.jobNumber, "123456");

	ltrim_line = trim ("  Job description . . : UXGZ  Library  . . . : MYLIB   ");
	jobProcessJobAttributes (ltrim_line, &jl, 3, "en");

	ck_assert_str_eq (jl.jobDescription, "UXGZ");
	ck_assert_str_eq (jl.jobLibrary, "MYLIB");

	ltrim_line = trim ("  Descripci�n trabajo . . . . . :  UXGZ  Biblioteca  . . . : MYLIB   ");
	jobProcessJobAttributes (ltrim_line, &jl, 3, "es");

	ck_assert_str_eq (jl.jobDescription, "UXGZ");
	ck_assert_str_eq (jl.jobLibrary, "MYLIB");

	free (ltrim_line);
} END_TEST

START_TEST (test_jobProcessMsgHeader)
{
	char *trim_line = NULL;

	trim_line = trim ("CPF1124   Information   00   14/04/20  11:39:30.870509  QWTPIIPP  QSYS   04C0  *EXT   *N ");
	jobProcessMsgHeader (trim_line, &jl);
	ck_assert_str_eq (jl.msgID, "CPF1124");
	ck_assert_str_eq (jl.msgType, "Information");
	ck_assert_str_eq (jl.msgSEV, "00");
	ck_assert_str_eq (jl.msgDatetime, "14/04/20 11:39:30.870509");
	ck_assert_str_eq (jl.msgFromPGM, "QWTPIIPP");
	ck_assert_str_eq (jl.msgFromPGMLibrary, "QSYS");
	ck_assert_str_eq (jl.msgFromPGMInst, "04C0");
	ck_assert_str_eq (jl.msgToPGM, "*EXT");
	ck_assert_str_eq (jl.msgToPGMLibrary, "n/a");
	ck_assert_str_eq (jl.msgToPGMInst, "*N");
	ck_assert_str_eq (jl.msg, "");

	free (trim_line);
} END_TEST

Suite *auditlog_suite (void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create ("auditLog tests");
	tc_core = tcase_create ("auditLog core");

	tcase_add_test (tc_core, test_audit_filename_and_hostname_struct_fields);
	tcase_add_test (tc_core, test_auditProcessLogHeader);
	tcase_add_test (tc_core, test_auditProcessLogPage);
	suite_add_tcase (s, tc_core);

	return s;
}

Suite *joblog_suite (void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create ("jobLog tests");
	tc_core = tcase_create ("jobLog core");

	tcase_add_test (tc_core, test_jobProcessLogHeader);
	tcase_add_test (tc_core, test_jobProcessPageHeader);
	tcase_add_test (tc_core, test_jobProcessLogPage);
	tcase_add_test (tc_core, test_jobProcessJobAttributes);
	tcase_add_test (tc_core, test_jobProcessMsgHeader);
	
	suite_add_tcase (s, tc_core);

	return s;
}

int main (void)
{
	int no_failed = 0;
	SRunner *sr;

	sr = srunner_create (auditlog_suite ());
	srunner_add_suite (sr, joblog_suite ());

	/* If the log name is set to "-" either via srunner_set_log(),
	the log data will be printed to stdout instead of to a file. */
	srunner_set_log (sr, "-");

	srunner_run_all (sr, CK_NORMAL);

	no_failed = srunner_ntests_failed (sr);

	srunner_free (sr);
	
	return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}