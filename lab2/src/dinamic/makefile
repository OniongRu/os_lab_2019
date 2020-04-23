task2: main.c revert_string.c
	gcc -o task2 main.c revert_string.c -I.
binary: main.o librevert.a
        gcc -o binary main.o -L. -lrevert

main.o: main.c
        gcc -c main.c

librevert.a: revert_string.o
        ar cr librevert.a revert_string.o

revert_string.o: revert_string.c
        gcc -c revert_string.c

clean:
	rm -f *.o *.a binary
