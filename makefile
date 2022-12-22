CC = gcc
CFLAGS = -Wall
objects = main.o agenda.o

run: main
	./main
	
all: main

main: agenda.o main.c
	$(CC) -o main agenda.o main.c
	
Lista.o: agenda.c agenda.h
	$(CC) -c agenda.c
	
clean:
	rm main $(objects)