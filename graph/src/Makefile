CC = gcc
CFLAGS = -Wall -Werror -Wextra

TARGET = ../build/graph
SRCS = graph.c parser.c rpn.c

BUILD_DIR = ../build
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
