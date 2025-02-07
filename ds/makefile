#Directories
INCLUDE_DIR = ./include
SRC_DIR = src
TEST_DIR = test

# Compiler and compilation flags
CC=gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -I$(INCLUDE_DIR)

# Build configuration flags
DEBUG = -g
RELEASE = -DNDEBUG -O3

# Build target and object files
TARGET=queue.out
OBJS=queue.o queue_test.o singly_ll.o

all: $(TARGET)

debug: CFLAGS += $(DEBUG)
debug: $(TARGET)

release: CFLAGS += $(RELEASE)
release: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

queue.o: $(SRC_DIR)/queue.c $(INCLUDE_DIR)/queue.h $(INCLUDE_DIR)/singly_ll.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/queue.c -o queue.o

queue_test.o: $(TEST_DIR)/queue_test.c $(INCLUDE_DIR)/queue.h
	$(CC) $(CFLAGS) -c $(TEST_DIR)/queue_test.c -o queue_test.o

singly_ll.o: $(SRC_DIR)/singly_ll.c $(INCLUDE_DIR)/singly_ll.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/singly_ll.c -o singly_ll.o
clean :
	rm -f $(OBJS) $(TARGET)


