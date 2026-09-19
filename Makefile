CC = gcc
CFLAGS = -Wall -Wextra -std=c17
TARGET = build/allin
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)
$(TARGET):$(OBJ)
	$(CC) $(OBJ) -o $(TARGET)
build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@
run: $(TARGET)
	./$(TARGET)
clean:
	rm -rf build/