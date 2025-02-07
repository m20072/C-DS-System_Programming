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

#below are what the implicit rules would do
#notice .h dependencies are missing, implicits are not reliable
#main.o: main.c		
#	$(CC) -c $(CPPFLAGS) $(CFLAGS)
	
#foo.o : foo.c
#	$(CC) -c $(CPPFLAGS) $(CFLAGS)

clean :
	rm -f $(OBJS) $(TARGET)

