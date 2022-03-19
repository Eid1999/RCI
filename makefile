# makefile

CC = gcc
CFLAGS = -Wall
LDFLAGS =
OBJFILES = ring.o newAnel.o
TARGET = ring
all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~
