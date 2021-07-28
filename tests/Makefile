
# Usage:
#  all: compile, link, and run all tests, and then delete binaries
#  run: compile, link, and run all tests 
#  runv: compile, link, and run tests verbosely
#  runl: compile, link, run, and monitor memory usage of tests (requires
#  valgrind)
#  memcheck: compile, link, run, and monitor memory usage of tests, then remove
#   binaries (requires valgrind)
#  clean: remove test binaries, if present
#  cleanall: remove test binaries and object files, if present

.PHONY = all run runv runl memcheck clean cleanall

CC = gcc
CFLAGS = -lm

BASE_DIR = $(HOME)/repos/raytracerchallenge
OBJ_DIR = $(BASE_DIR)/obj
SRC_DIR = $(BASE_DIR)/src
INCLUDE_DIR = $(BASE_DIR)/include
TESTS_DIR = $(BASE_DIR)/tests
UNITY_DIR = $(TESTS_DIR)/Unity

TEST_SRC := $(TESTS_DIR)/*.c
UNITY_SRC := $(UNITY_DIR)/*.c
PROJECT_SRC := $(SRC_DIR)/*.c

OBJECT_FILES = AllTests.o \
	        Utilities.o \
		Tuple.o \
		Color.o \
		Canvas.o \
		Matrix.o \
		Transformations.o \
		UtilitiesTest.o \
		UtilitiesTestRunner.o \
		TupleTest.o \
		TupleTestRunner.o \
		ColorTest.o \
		ColorTestRunner.o \
		CanvasTest.o \
		CanvasTestRunner.o \
		MatrixTest.o \
		MatrixTestRunner.o \
		TransformationsTest.o \
		TransformationsTestRunner.o \
		unity_fixture.o \
		unity_memory.o \
		unity.o


SRC := $(UNITY_SRC) $(TEST_SRC) $(PROJECT_SRC)
OBJ := $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJECT_FILES))

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
	@echo -n "Compiling "$@"..."
	@$(CC) -c -I $(UNITY_DIR) -I $(INCLUDE_DIR) $< -o $@
	@echo "Done."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h
	@echo -n "Compiling "$@"..."
	@$(CC) -c -I $(INCLUDE_DIR) $< -o $@
	@echo "Done."

$(OBJ_DIR)/%.o: $(UNITY_DIR)/%.c $(UNITY_DIR)/%.h
	@echo -n "Compiling "$@"..."
	@$(CC) -c -I $(INCLUDE_DIR) $< -o $@
	@echo "Done."

