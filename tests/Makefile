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

.PHONY = all run runv verbose runl memcheck clean cleanall

CC = gcc
CFLAGS = -lm

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

run: AllTests.test
	@echo "Running tests..."
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@-./AllTests.test
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
	@-valgrind --leak-check=yes ./AllTests.test
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@echo "Done."

memcheck: runl clean

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
	@$(CC) $(CFLAGS) $(OBJ) -o AllTests.test
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

