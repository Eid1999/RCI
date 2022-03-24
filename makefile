# makefile

CC = gcc
CFLAGS = -g  -Wall
LDFLAGS =
SOURCES=ring.c interface.c mensagem_tcp.c sub_processo.c mensagem_udp.c  ACK.c
OBJFILES = ring.o interface.o mensagem_tcp.o sub_processo.o mensagem_udp.o  ACK.o
TARGET = ring

all:$(TARGET)

$(TARGET):$(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c Anel.h
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(TARGET) $(OBJFILES)
	
