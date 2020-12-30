#include <check.h>
#include <unistd.h>
#include "../src/auditlog2json.h"

char *filename = "test_audit.log";

INIT_AUDITLOG(al);

START_TEST(test_filename_and_hostname_struct_fields)
{
	// Set audit log file name as fileName field in auditLog struct.
	strcpy (al.fileName, filename);

	// Set host name as serverName field in auditLog struct.
	gethostname (al.serverName, SERVER_NAME_MAXSTRLEN);

	char serverName[SERVER_NAME_MAXSTRLEN];
    gethostname (serverName, SERVER_NAME_MAXSTRLEN);

	ck_assert_str_eq (al.fileName, filename);
	ck_assert_str_eq (al.serverName, serverName);
} END_TEST

START_TEST(test_header_struct_fileds)
{
	char *trim_line = NULL;
	
	trim_line = trim ("     QUERY NAME . . QSECCD");
	processLogHeader (trim_line, &al, 0);
	ck_assert_str_eq (al.headerQueryName, "QSECCD");
	
	trim_line = trim ("     LIBRARY NAME . . QSYS");
	processLogHeader (trim_line, &al, 1);
	ck_assert_str_eq (al.headerLibraryName, "QSYS");

	trim_line = trim ("     QASYCDJ4  QTEMP    QASYCDJ4  QASYCDJ4");
	processLogHeader (trim_line, &al, 3);
	ck_assert_str_eq (al.headerFile, "QASYCDJ4");
	ck_assert_str_eq (al.headerLibrary, "QTEMP");
	ck_assert_str_eq (al.headerMember, "QASYCDJ4");
	ck_assert_str_eq (al.headerFormat, "QASYCDJ4");
	
	trim_line = trim ("     DATE . . . . . . . 14/04/20");
	processLogHeader (trim_line, &al, 4);
	ck_assert_str_eq (al.headerDate, "14/04/20");

	trim_line = trim ("     TIME . . . . . . . 01:03:07");
	processLogHeader (trim_line, &al, 5);
	ck_assert_str_eq (al.headerTime, "01:03:07");

	free(trim_line);
} END_TEST

START_TEST(test_page_struct_fileds)
{
	char *trim_line = NULL;
	int n_msgs = 0;
	trim_line = trim ("CD   C   MIMIXOWN   CHKOBJ   QSYS     E   RCV_RUNCMD MIMIXOWN  481053 2020-04-14-00.00.00.045045");
	
	processLogPage (trim_line, &al, &n_msgs);

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

	free(trim_line);
} END_TEST

Suite *auditlog_struct_suite (void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Test auditLog struct");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_filename_and_hostname_struct_fields);
	tcase_add_test(tc_core, test_header_struct_fileds);
	tcase_add_test(tc_core, test_page_struct_fileds);
	suite_add_tcase(s, tc_core);

	return s;
}

int main (void)
{
	int no_failed = 0;
	Suite *s;
	SRunner *runner;

	s = auditlog_struct_suite ();
	runner = srunner_create (s);

	srunner_run_all (runner, CK_NORMAL);
	no_failed = srunner_ntests_failed (runner);
	srunner_free (runner);
	return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}