
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

projectile.out: $(OBJ_DIR)/projectile.o $(OBJ_DIR)/Tuple.o $(OBJ_DIR)/Canvas.o $(OBJ_DIR)/Color.o
	@echo -n "Linking projectile.out..." 
	@$(CC) $(CFLAGS) $^ -o $@ 
	@echo "Done."

$(OBJ_DIR)/projectile.o: projectile.c $(INCLUDE_DIR)/Tuple.h $(INCLUDE_DIR)/Canvas.h 
	@echo -n "Compiling projectile.c..." 
	@$(CC) -c $(CFLAGS) -I $(INCLUDE_DIR) $< -o $@ 
	@echo "Done."

$(OBJ_DIR)/Canvas.o: Canvas.c $(INCLUDE_DIR)/Canvas.h $(INCLUDE_DIR)/Color.h
	@echo -n "Compiling "$<"..." 
	@$(CC) -c $(CFLAGS) -I $(INCLUDE_DIR) $< -o $@ 
	@echo "Done."

$(OBJ_DIR)/%.o: %.c $(INCLUDE_DIR)/%.h
	@echo -n "Compiling "$<"..." 
	@$(CC) -c $(CFLAGS) -I $(INCLUDE_DIR) $< -o $@ 
	@echo "Done."
