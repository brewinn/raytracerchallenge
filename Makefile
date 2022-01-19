# Usage:
#  all: compile, link, and run all tests and sources, then delete binaries
#  test: compile, link, and run all tests, then delete binaries
#  program: compile, link, and run all programs then delete binaries
#  memcheck: compile, link, and check test binary for memory leaks (requires
#  valgrind)
#  verbose: compile, link, and run all tests with the verbose option, then
#  delete binaries
#  buildclean: compile, link, and run tests and programs after removing all
#  objects and binaries
#  clean: remove binaries, if present
#  cleanall: remove binaries and object files, if present
#
# The following commands are used primarily for github actions:
#  build: compile, but do not link, the files in the source directory
#  memtest: run a memory check, but do not suppress errors produced by valgrind
#  testcheck: run the tests, but do not suppress errors

.PHONY = all test testcheck program memcheck memtest verbose buildclean build clean cleanall

BASE_DIR = .
SRC_DIR = $(BASE_DIR)/src
OBJ_DIR = $(BASE_DIR)/obj
PROGRAM_DIR = $(BASE_DIR)/main
TESTS_DIR = $(BASE_DIR)/tests

all: test program

test:
	@echo "Compiling and running tests..."
	@echo "================================"
	@$(MAKE) -C $(TESTS_DIR)
	@echo "================================"
	@echo "Done."

testcheck:
	@echo "Compiling and running tests..."
	@echo "================================"
	@$(MAKE) -C $(TESTS_DIR) check
	@echo "================================"
	@echo "Done."

program:
	@echo "Compiling and running programs..."
	@echo "================================"
	@$(MAKE) -C $(PROGRAM_DIR)
	@echo "================================"
	@echo "Done."

memcheck:
	@echo "Checking tests for memory leaks..."
	@echo "================================"
	@$(MAKE) -C $(TESTS_DIR) memcheck
	@echo "================================"
	@echo "Done."

memtest:
	@echo "Checking tests for memory leaks..."
	@echo "================================"
	@$(MAKE) -C $(TESTS_DIR) memtest
	@echo "================================"
	@echo "Done."

verbose:
	@echo "Running tests with verbose option..."
	@echo "================================"
	@$(MAKE) -C $(TESTS_DIR) verbose
	@echo "================================"
	@echo "Done."

buildclean: cleanall all

build:
	@echo "Compiling sources..."
	@echo "================================"
	@$(MAKE) -C $(SRC_DIR)
	@echo "================================"
	@echo "Done."

clean:
	@echo "Removing test binaries..."
	@echo "================================"
	@$(MAKE) -C $(TESTS_DIR) clean
	@echo "================================"
	@echo "Done."
	@echo "Removing program binaries..."
	@echo "================================"
	@$(MAKE) -C $(PROGRAM_DIR) clean
	@echo "================================"
	@echo "Done."

cleanall: clean
	@echo -n "Removing object files..."
	@rm -rf $(wildcard $(OBJ_DIR)/*.o)
	@echo "Done."
