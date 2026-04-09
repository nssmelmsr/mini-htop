CC = gcc
CFLAGS = -Wall

SRC = src/main.c src/cpu.c src/proc.c
OBJ = $(SRC:.c=.o)

htop: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o minihtop

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o minihtop