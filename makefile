CC = gcc
CFLAGS = -Wall

all: main cpuread 

main:

	$(CC) $(CFLAGS) src/main.c -o htop

cpuread: 

	$(CC) $(CFLAGS) src.c -o cpu

clean:

	rm -f mycat myls mywc