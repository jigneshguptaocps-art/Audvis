CC     = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = Audvis

all: $(TARGET)

$(TARGET): Audvis.c
	$(CC) $(CFLAGS) -o $(TARGET) Audvis.c

clean:
	rm -f $(TARGET)

.PHONY: all clean
