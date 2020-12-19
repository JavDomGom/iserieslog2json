CC=gcc
CFLAGS=-Wall -g
PROGRAM_NAME=main
TEST_NAME=test
DEPS=auditlogreader.c auditlogreader.h

main: $(PROGRAM_NAME).c $(DEPS)
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME) $(PROGRAM_NAME).c $(DEPS)

test: $(TEST_NAME).c
	$(CC) $(CFLAGS) -o $(TEST_NAME) $(TEST_NAME).c