CC = gcc
CFLAGS = -Wall -g -Iinclude

SRC = src/main.c src/parser.c src/executor.c src/builtins.c src/path.c src/redirect.c src/parallel.c
OBJ = $(SRC:.c=.o)

TARGET = wish

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm -f src/*.o $(TARGET)