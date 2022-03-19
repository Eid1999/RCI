# makefile

CC = gcc
CFLAGS = -g  -Wall
LDFLAGS =
SOURCES=newAnel.c ring.c
OBJFILES = ring.o newAnel.o
TARGET = ring

all:$(TARGET)

$(TARGET):$(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c Anel.h
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(TARGET) $(OBJFILES)
	
