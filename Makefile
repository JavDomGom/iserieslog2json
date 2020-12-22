CC=gcc
CFLAGS=-Wall -g
PROGRAM_NAME=auditlog2json
DEPS=$(PROGRAM_NAME).c $(PROGRAM_NAME).h

build: main.c $(DEPS)
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME) main.c $(DEPS)