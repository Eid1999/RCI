# makefile

CC = gcc
CFLAGS = -g  -Wall
LDFLAGS =
SOURCES=ring.c interface.c pentry.c sub_tcp.c
OBJFILES = ring.o interface.o pentry.o sub_tcp.o
TARGET = ring

all:$(TARGET)

$(TARGET):$(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c Anel.h
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(TARGET) $(OBJFILES)
	
