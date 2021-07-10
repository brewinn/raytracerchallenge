
# Usage:
#  all: compile, link, and run all programs, and then delete binaries
#  run: compile, link, and run all programs 
#  clean: remove program binaries, if present
#  cleanall: remove programs binaries and object files, if present

.PHONY = all run clean cleanall

CC = gcc
CFLAGS = -lm

BASE_DIR = $(HOME)/repos/raytracerchallenge
OBJ_DIR = $(BASE_DIR)/obj
SRC_DIR = $(BASE_DIR)/src
INCLUDE_DIR = $(BASE_DIR)/include

BIN := projectile.out

all: run clean

run: $(BIN)
	@echo "Running "$<"..."
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@./$(BIN)
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@echo "Done."

clean:
	@echo -n "Removing program binaries..."
	@rm -rf $(BIN)
	@echo "Done."

cleanall: clean
	@echo -n "Removing object files..."
	@rm -rf $(wildcard $(OBJ_DIR)/*.o)
	@echo "Done."

projectile.out: $(OBJ_DIR)/projectile.o $(OBJ_DIR)/Tuple.o
	@echo -n "Linking projectile.out..." 
	@$(CC) $(CFLAGS) $^ -o $@ 
	@echo "Done."

$(OBJ_DIR)/projectile.o: projectile.c $(INCLUDE_DIR)/Tuple.h
	@echo -n "Compiling projectile.c..." 
	@$(CC) -c $(CFLAGS) -I $(INCLUDE_DIR) $< -o $@ 
	@echo "Done."

$(OBJ_DIR)/Tuple.o: Tuple.c $(INCLUDE_DIR)/Tuple.h
	@echo -n "Compiling Tuple.c..." 
	@$(CC) -c $(CFLAGS) -I $(INCLUDE_DIR) $< -o $@ 
	@echo "Done."
