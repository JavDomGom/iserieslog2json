CC=gcc
CFLAGS=-Wall -g
PROGRAM_NAME=auditlog2json
DEPS=main.c $(PROGRAM_NAME).c $(PROGRAM_NAME).h
PREFIX=/usr/local/bin
VALGRINDFLAGS=--tool=memcheck --leak-check=full --show-leak-kinds=all -v

all: build install clean

build: $(DEPS)
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME) $(DEPS)

clean: $(PROGRAM_NAME)
	@echo "Clean binaries ..."
	rm -f $(PROGRAM_NAME)
	@echo "Done!"

install: $(PROGRAM_NAME)
	@echo "Installing $(PROGRAM_NAME) ..."
	install -m 0755 $(PROGRAM_NAME) $(PREFIX)
	@echo "Done!"

uninstall:
	@echo "Uninstall $(PROGRAM_NAME) from $(PREFIX) ..."
	rm -f $(PREFIX)/$(PROGRAM_NAME)
	@echo "Done!"

valgrind: $(PROGRAM_NAME)
	valgrind $(VALGRINDFLAGS) ./$(PROGRAM_NAME) -f $(FILE) > /dev/null

.PHONY: all build clean install uninstall valgrind