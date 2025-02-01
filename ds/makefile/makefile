CC=gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
DEBUG = -g
RELEASE = -DNDEBUG -O3
TARGET=fooer.out
OBJS=main.o foo.o

all: $(TARGET)

debug: CFLAGS += $(DEBUG)
debug: $(TARGET)

release: CFLAGS += $(RELEASE)
release: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@


main.o: main.c foo.h
	$(CC) $(CFLAGS) -c main.c
	
foo.o : foo.c foo.h
	$(CC) $(CFLAGS) -c foo.c

clean :
	rm -f $(OBJS) $(TARGET)

