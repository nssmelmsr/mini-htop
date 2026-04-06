CC = gcc
CFLAGS = -Wall

all: main 

main:

	$(CC) $(CFLAGS) src/main.c src/cpu.c -o htop

clean:

	rm -f htop