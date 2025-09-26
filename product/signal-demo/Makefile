CC = gcc
CFLAGS = -Wall -O2
TARGET = signal

all: $(TARGET)

$(TARGET): signal.c
	$(CC) $(CFLAGS) -o $(TARGET) signal.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
