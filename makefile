# makefile

CC = gcc
CFLAGS = -g  -Wall
LDFLAGS =
SOURCES=newAnel.c ring.c
OBJFILES = ring.o
OUTPUT = ring

$(OUTPUT): $(OBJFILES)
	$(CC)  $(CFLAGS) $(SOURCES)   -o $(OUTPUT) $(LDFLAGS)
	
clean:
	rm -f $(OBJFILES) $(TARGET) *~


