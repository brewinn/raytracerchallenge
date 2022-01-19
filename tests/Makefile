# Usage:
#  all: compile, link, and run all tests, and then delete binaries
#  run: compile, link, and run all tests 
#  runv: compile, link, and run tests verbosely
#  verbose: compile, link, and run tests verbosely, then delete binaries
#  runl: compile, link, run, and monitor memory usage of tests (requires
#  valgrind)
#  memcheck: compile, link, run, and monitor memory usage of tests, then remove
#   binaries (requires valgrind)
#  clean: remove test binaries, if present
#  cleanall: remove test binaries and object files, if present
#
# The following commands are used primarily for github actions:
#  rune: compile, link, and run all tests without suppressing errors
#  runle: compile, link, run, and monitor memory usage of tests without
#   suppressing errors
#  memtest: same as memcheck, but don't suppress errors
#  check: same as all, but don't suppress errors

.PHONY = all check rune runv verbose runl runle memcheck memtest clean cleanall

CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99 -pedantic
LFLAGS = -lm

BASE_DIR = ..
OBJ_DIR = $(BASE_DIR)/obj
SRC_DIR = $(BASE_DIR)/src
INCLUDE_DIR = $(BASE_DIR)/include
TESTS_DIR = $(BASE_DIR)/tests
UNITY_DIR = $(TESTS_DIR)/Unity

vpath %.h $(INCLUDE_DIR)
vpath %.h $(UNITY_DIR)
vpath %.c $(SRC_DIR)
vpath %.c $(TESTS_DIR)
vpath %.c $(UNITY_DIR)

TEST_SRC := $(wildcard $(TESTS_DIR)/*.c)
UNITY_SRC := $(wildcard $(UNITY_DIR)/*.c)
PROJECT_SRC := $(wildcard $(SRC_DIR)/*.c)

SRC := $(UNITY_SRC) $(TEST_SRC) $(PROJECT_SRC)

SRC_FILES = $(notdir $(SRC))

OBJ := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

TEST_BINS := AllTests.test

all: run clean

check: rune clean

run: AllTests.test
	@echo "Running tests..."
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@-./AllTests.test
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@echo "Done."

rune: AllTests.test
	@echo "Running tests..."
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@./AllTests.test
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@echo "Done."

runv: AllTests.test
	@echo "Running tests verbosely..."
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@-./AllTests.test -v
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@echo "Done."

verbose: runv clean

runl: AllTests.test
	@echo "Running tests with memcheck..."
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@-valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./AllTests.test
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@echo "Done."

runle: AllTests.test
	@echo "Checking tests for memory errors..."
	@valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes ./AllTests.test
	@echo "Done."

memcheck: runl clean

memtest: runle clean

clean:
	@echo -n "Cleaning up test binaries..."
	@rm -rf $(TEST_BINS)
	@echo "Done."

cleanall:
	@echo -n "Cleaning up objects and binaries..."
	@rm -rf $(TEST_BINS)
	@rm -rf $(OBJ)
	@echo "Done."

AllTests.test: $(OBJ)
	@echo -n "Linking all tests..."
	@$(CC) $(OBJ) -o AllTests.test $(LFLAGS)
	@echo "Done."

$(OBJ_DIR)/%.o: %.c
	@echo -n "Compiling "$(notdir $@)"..."
	@$(CC) -c -I $(UNITY_DIR) -I $(INCLUDE_DIR) $< -o $@
	@echo "Done."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h
	@echo -n "Compiling "$(notdir $@)"..."
	@$(CC) -c -I $(INCLUDE_DIR) $< -o $@
	@echo "Done."

$(OBJ_DIR)/%.o: $(UNITY_DIR)/%.c $(UNITY_DIR)/%.h
	@echo -n "Compiling "$(notdir $@)"..."
	@$(CC) -c -I $(INCLUDE_DIR) $< -o $@
	@echo "Done."

