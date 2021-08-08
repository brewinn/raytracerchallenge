
# Usage:
#  all: compile, link, and run all programs, and then delete binaries
#  run: compile, link, and run all programs 
#  projectile: compile, link, and run projectile program
#  clockface: compile, link, and run clockface program
#  sphereCast: compile, link, and run sphereCast program
#  clean: remove program binaries, if present
#  cleanall: remove programs binaries and object files, if present

.PHONY = all run projectile clockface sphereCast clean cleanall

CC = gcc
CFLAGS = -lm

BASE_DIR = ..
OBJ_DIR = $(BASE_DIR)/obj
INCLUDE_DIR = $(BASE_DIR)/include

BIN := projectile.out \
       clockface.out \
       sphereCast.out

all: run clean

run: projectile clockface sphereCast

projectile: projectile.out
	@echo "Running "$<"..."
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@./projectile.out
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@echo "Done."

clockface: clockface.out
	@echo -n "Running "$<"..."
	@./clockface.out
	@echo "Done."

sphereCast: sphereCast.out
	@echo -n "Running "$<"..."
	@./sphereCast.out
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

projectile.out: $(OBJ_DIR)/projectile.o $(OBJ_DIR)/Tuple.o $(OBJ_DIR)/Canvas.o $(OBJ_DIR)/Color.o $(OBJ_DIR)/Utilities.o
	@echo -n "Linking projectile.out..." 
	@$(CC) $(CFLAGS) $^ -o $@ 
	@echo "Done."

clockface.out: $(OBJ_DIR)/clockface.o $(OBJ_DIR)/Transformations.o $(OBJ_DIR)/Matrix.o $(OBJ_DIR)/Tuple.o $(OBJ_DIR)/Canvas.o $(OBJ_DIR)/Color.o $(OBJ_DIR)/Utilities.o
	@echo -n "Linking clockface.out..." 
	@$(CC) $(CFLAGS) $^ -o $@ 
	@echo "Done."

sphereCast.out: $(OBJ_DIR)/sphereCast.o $(OBJ_DIR)/Canvas.o $(OBJ_DIR)/Color.o $(OBJ_DIR)/Sphere.o $(OBJ_DIR)/Ray.o $(OBJ_DIR)/Intersection.o $(OBJ_DIR)/Transformations.o $(OBJ_DIR)/Matrix.o $(OBJ_DIR)/Tuple.o $(OBJ_DIR)/Utilities.o
	@echo -n "Linking sphereCast.out..." 
	@$(CC) $(CFLAGS) $^ -o $@ 
	@echo "Done."

### Objects ###

$(OBJ_DIR)/projectile.o: projectile.c $(INCLUDE_DIR)/Tuple.h $(INCLUDE_DIR)/Canvas.h 
	@echo -n "Compiling projectile.c..." 
	@$(CC) -c $(CFLAGS) -I $(INCLUDE_DIR) $< -o $@ 
	@echo "Done."

$(OBJ_DIR)/clockface.o: clockface.c $(INCLUDE_DIR)/Transformations.h $(INCLUDE_DIR)/Canvas.h
	@echo -n "Compiling clockface.c..." 
	@$(CC) -c $(CFLAGS) -I $(INCLUDE_DIR) $< -o $@ 
	@echo "Done."

$(OBJ_DIR)/sphereCast.o: sphereCast.c $(INCLUDE_DIR)/Canvas.h
	@echo -n "Compiling sphereCast.c..." 
	@$(CC) -c $(CFLAGS) -I $(INCLUDE_DIR) $< -o $@ 
	@echo "Done."

$(OBJ_DIR)/%.o: %.c $(INCLUDE_DIR)/%.h
	@echo -n "Compiling "$<"..." 
	@$(CC) -c $(CFLAGS) -I $(INCLUDE_DIR) $< -o $@ 
	@echo "Done."
