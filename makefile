# makefile

CC = gcc
CFLAGS = -g  -Wall
LDFLAGS =
SOURCES=ring.c interface.c mensagem_tcp.c sub_tcp.c mensagem_udp.c sub_udp.c
OBJFILES = ring.o interface.o mensagem_tcp.o sub_tcp.o mensagem_udp.o sub_udp.o
TARGET = ring

all:$(TARGET)

$(TARGET):$(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c Anel.h
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(TARGET) $(OBJFILES)
	
