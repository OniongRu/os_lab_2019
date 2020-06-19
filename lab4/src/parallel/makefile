CC=gcc
CFLAGS=-I.

all: parallel_min_max

parallel_min_max : utils.o find_min_max.o parallel_min_max.o
	$(CC) -o parallel_min_max utils.o find_min_max.o parallel_min_max.o $(CFLAGS)

parallel_min_max.o: parallel_min_max.c
	$(CC) -o parallel_min_max.o -c parallel_min_max.c $(CFLAGS)

utils.o : utils.h utils.c
	$(CC) -o utils.o -c utils.c $(CFLAGS)

find_min_max.o : utils.h find_min_max.h find_min_max.c
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)

clean :
	rm find_min_max.o utils.o parallel_min_max.o parallel_min_max
