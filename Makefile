CC=gcc
CFLAGS=-Wall -g
PROGRAM_NAME=auditlog2json
DEPS=$(PROGRAM_NAME).c $(PROGRAM_NAME).h
VALGRINDFLAGS=--tool=memcheck --leak-check=full -v

build: main.c $(DEPS)
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME) main.c $(DEPS)

valgrind: $(PROGRAM_NAME)
	valgrind $(VALGRINDFLAGS) ./$(PROGRAM_NAME) -f $(FILE) > /dev/null