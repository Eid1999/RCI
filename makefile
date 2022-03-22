# makefile

CC = gcc
CFLAGS = -g  -Wall
LDFLAGS =
SOURCES=ring.c interface.c mensagem_tcp.c sub_tcp.c
OBJFILES = ring.o interface.o mensagem_tcp.o sub_tcp.o
TARGET = ring

all:$(TARGET)

$(TARGET):$(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c Anel.h
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(TARGET) $(OBJFILES)
	
