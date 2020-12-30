CC=gcc
CFLAGS=-Wall -g
PROGRAM_NAME=auditlog2json
PREFIX=/usr/local/bin
VALGRINDFLAGS=--tool=memcheck --leak-check=full --show-leak-kinds=all -v
PROFILE_FLAGS=-fprofile-arcs -ftest-coverage
TST_LIBS=-lcheck -lm -lpthread -lrt -lsubunit
COV_LIBS=-lgcov -coverage
SRC_DIR=src
TST_DIR=tests
SRC_FILES=$(addprefix $(SRC_DIR)/, *.c)
LIB_FILES=$(addprefix $(SRC_DIR)/, $(PROGRAM_NAME).*)
TST_FILES=$(addprefix $(TST_DIR)/, *.c)
GCOV=gcovr
GCONV_FLAGS=-r . --html --html-details

all: coverage_report.html

$(PROGRAM_NAME).o: $(LIB_FILES)
	$(CC) -c $(CFLAGS) $(PROFILE_FLAGS) $(LIB_FILES)

check_$(PROGRAM_NAME).o: $(TST_FILES)
	$(CC) -c $(CFLAGS) $(PROFILE_FLAGS)  $(TST_FILES)

check_$(PROGRAM_NAME)_tests: $(PROGRAM_NAME).o check_$(PROGRAM_NAME).o
	$(CC) $(PROGRAM_NAME).o check_$(PROGRAM_NAME).o $(TST_LIBS) $(COV_LIBS) -o check_$(PROGRAM_NAME)_tests

test: check_$(PROGRAM_NAME)_tests
	./check_$(PROGRAM_NAME)_tests

coverage_report.html: test
	$(GCOV) $(GCONV_FLAGS) -o coverage_report.html

build: $(SRC_FILES)
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME) $(SRC_FILES)

install: build
	@echo "Installing $(PROGRAM_NAME) ..."
	install -m 0755 $(PROGRAM_NAME) $(PREFIX)
	@echo "Done!"

uninstall: $(PREFIX)/$(PROGRAM_NAME)
	@echo "Uninstall $(PROGRAM_NAME) from '$(PREFIX)' ..."
	rm -f $(PREFIX)/$(PROGRAM_NAME)
	@echo "Done!"

valgrind: build
	valgrind $(VALGRINDFLAGS) ./$(PROGRAM_NAME) -f $(FILE) > /dev/null

clean:
	rm -f *.o *.html *.gcda *.gcno $(addprefix $(SRC_DIR)/, *.gch) *$(PROGRAM_NAME)*

.PHONY: all test build install uninstall valgrind clean