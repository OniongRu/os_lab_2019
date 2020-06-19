CC=gcc
CFLAGS=-I.
PTH=parallel/

all: parallel_min_max process_memory

parallel_sum : parallel_sum.c  utils.o utils.h
	$(CC) -o parallel_sum utils.o  parallel_sum.c -lpthread $(CFLAGS)

process_memory : process_memory.c
	$(CC) -o process_memory process_memory.c $(CFLAGS) 

parallel_min_max : utils.o find_min_max.o parallel_min_max.o
	$(CC) -o parallel_min_max utils.o find_min_max.o parallel_min_max.o $(CFLAGS)

parallel_min_max.o: $(PTH)parallel_min_max.c
	$(CC) -o parallel_min_max.o -c $(PTH)parallel_min_max.c $(CFLAGS)

utils.o : $(PTH)utils.h $(PTH)utils.c
	$(CC) -o utils.o -c $(PTH)utils.c $(CFLAGS)

find_min_max.o : $(PTH)utils.h $(PTH)find_min_max.h $(PTH)find_min_max.c
	$(CC) -o find_min_max.o -c $(PTH)find_min_max.c $(CFLAGS)

cleanO:
	rm find_min_max.o utils.o parallel_min_max.o

clean :
	rm find_min_max.o utils.o parallel_min_max.o parallel_min_max process_memory
