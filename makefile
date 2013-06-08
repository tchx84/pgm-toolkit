CC=gcc
CFLAGS=-O3 -march=native

all: exercises/exercises

exercises/exercises: exercises/exercises.o lib/pgm.o lib/queue.o
	$(CC) $(CFLAGS) -o exercises/exercises exercises/exercises.o lib/pgm.o lib/queue.o

exercises/exercises.o: exercises/exercises.c
	$(CC) $(CFLAGS) -o exercises/exercises.o -c exercises/exercises.c;

lib/pgm.o: lib/pgm.c
	$(CC) $(CFLAGS) -o lib/pgm.o -c lib/pgm.c;

lib/queue.o: lib/queue.c
	$(CC) $(CFLAGS) -o lib/queue.o -c lib/queue.c;

clean:
	rm -rf exercises/exercises exercises/exercises.o lib/queue.o lib/pgm.o exercises/output.pgm exercises/output/*
