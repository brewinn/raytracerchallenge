# Usage:
#  all: compile, link, and run all programs, and then delete binaries
#  run: compile, link, and run all programs 
#  projectile: compile, link, and run projectile program
#  clockface: compile, link, and run clockface program
#  sphereCast: compile, link, and run sphereCast program
#  clean: remove program binaries, if present
#  cleanall: remove programs binaries and object files, if present

.PHONY = all run projectile clockface sphereCast clean cleanall
.SECONDARY:; # Prevents make from removing program object files

CC = gcc
CFLAGS = -lm

BASE_DIR = ..
SRC_DIR = $(BASE_DIR)/src
OBJ_DIR = $(BASE_DIR)/obj
INCLUDE_DIR = $(BASE_DIR)/include

vpath %.h $(INCLUDE_DIR)
vpath %.c $(SRC_DIR)

SRC_FILES := $(notdir $(wildcard $(SRC_DIR)/*.c))
OBJ_FILES := $(patsubst %.c, %.o, $(SRC_FILES))
DEP_FILES := $(patsubst %.o, %.d, $(OBJ_FILES))

OBJ := $(addprefix $(OBJ_DIR)/,$(OBJ_FILES))
BIN := projectile.program \
       clockface.program \
       sphereCast.program

all: run clean

run: projectile clockface sphereCast

projectile: projectile.program
	@echo "Running "$<"..."
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@./projectile.program
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@echo "Done."

clockface: clockface.program
	@echo -n "Running "$<"..."
	@./clockface.program
	@echo "Done."

sphereCast: sphereCast.program
	@echo -n "Running "$<"..."
	@./sphereCast.program
	@echo "Done."

clean:
	@echo -n "Removing program binaries..."
	@rm -rf $(BIN)
	@echo "Done."

cleanall: clean
	@echo -n "Removing object files..."
	@rm -rf $(wildcard $(OBJ_DIR)/*.o)
	@echo "Done."

### Binaries ###

%.program: $(OBJ_DIR)/%.o $(OBJ)
	@echo -n "Linking "$(notdir $<)"..." 
	@$(CC) $(CFLAGS) $^ -o $@ 
	@echo "Done."

### Objects ###

$(OBJ_DIR)/%.o: %.c 
	@echo -n "Compiling "$<"..." 
	@$(CC) -c $(CFLAGS) -I $(INCLUDE_DIR) $< -o $@ 
	@echo "Done."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h
	@echo -n "Compiling "$<"..." 
	@$(CC) -c $(CFLAGS) -I $(INCLUDE_DIR) $< -o $@ 
	@echo "Done."
