
# Usage:
#  all: compile, link, and run all tests and sources, then delete binaries
#  test: compile, link, and run all tests, then delete binaries
#  program: compile, link, and run all programs then delete binaries
#  memcheck: compile, link, and check test binary for memory leaks (requires
#  valgrind)
#  clean: remove binaries, if present
#  cleanall: remove binaries and object files, if present

.PHONY = all test program memcheck clean cleanall

BASE_DIR = .
OBJ_DIR = $(BASE_DIR)/obj
SRC_DIR = $(BASE_DIR)/src
TESTS_DIR = $(BASE_DIR)/tests

all: test program

test:
	@echo "Compiling and running tests..."
	@echo "================================"
	@$(MAKE) -C $(TESTS_DIR)
	@echo "================================"
	@echo "Done."

program:
	@echo "Compiling and running programs..."
	@echo "================================"
	@$(MAKE) -C $(SRC_DIR)
	@echo "================================"
	@echo "Done."
memcheck:
	@echo "Checking tests for memory leaks..."
	@echo "================================"
	@$(MAKE) -C $(TESTS_DIR) memcheck
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
	@$(MAKE) -C $(SRC_DIR) clean
	@echo "================================"
	@echo "Done."

cleanall: clean
	@echo -n "Removing object files..."
	@rm -rf $(wildcard $(OBJ_DIR)/*.o)
	@echo "Done."
