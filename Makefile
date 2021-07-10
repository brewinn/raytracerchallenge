
# Usage:
#  all: compile, link, and run all tests and sources, and then delete binaries
#  test: compile, link, and run all tests 
#  cleanall: remove binaries and object files, if present

.PHONY = all test cleanall

BASE_DIR = $(HOME)/repos/raytracerchallenge
OBJ_DIR = $(BASE_DIR)/obj
SRC_DIR = $(BASE_DIR)/src
TESTS_DIR = $(BASE_DIR)/tests

all: test

test:
	@echo "Compiling tests..."
	@echo "================================"
	@$(MAKE) -C $(TESTS_DIR)
	@echo "================================"
	@echo "Done."

cleanall:
	@echo "Removing test binaries..."
	@echo "================================"
	@$(MAKE) -C $(TESTS_DIR) clean
	@echo "================================"
	@echo "Done."

