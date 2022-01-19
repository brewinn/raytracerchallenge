# Usage:
#  all: compile all c files in source directory

.PHONY = all

CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99 -pedantic
LFLAGS = -lm

BASE_DIR = ..
OBJ_DIR = $(BASE_DIR)/obj
SRC_DIR = $(BASE_DIR)/src
INCLUDE_DIR = $(BASE_DIR)/include

vpath %.h $(INCLUDE_DIR)
vpath %.c $(SRC_DIR)

SRC := $(wildcard $(SRC_DIR)/*.c)

SRC_FILES = $(notdir $(SRC))

OBJ := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(OBJ)
	@echo "Finished compilation."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h
	@echo -n "Compiling "$(notdir $@)"..."
	@$(CC) -c -I $(INCLUDE_DIR) $< -o $@
	@echo "Done."

