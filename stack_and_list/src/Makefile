CC = gcc
CFLAGS = -c  -Wall -Werror -Wextra

# SRC1 = dmanager_module.c
SRC2 = list.c list_test.c
SRC3 = stack.c stack_test.c

# OBJ1=$(SRC1:.c=.o)
OBJ2=$(SRC2:.c=.o)
OBJ3 = $(SRC3:.c=.o)

BUILD_DIR = ../build
# EXE1 = $(BUILD_DIR)/Quest_1
EXE2 = $(BUILD_DIR)/Quest_2
EXE3 = $(BUILD_DIR)/Quest_3


.PHONY: all clean rebuild

# all: door_struct list_test stack_test
all: list_test stack_test

# door_struct: $(OBJ1)
# 	$(CC) $^ -o $(EXE1)

list_test: $(OBJ2)
	$(CC) $^ -o $(EXE2)

stack_test: $(OBJ3)
	$(CC) $^ -o $(EXE3)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BUILD_DIR)/*

rebuild: clean all

