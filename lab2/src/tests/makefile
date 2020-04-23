binary: test.o ../revert_string_dinamic/libvert.so
	gcc -o binary test.o -L. -lrevert -Wl,-rpath,.
test.o: test.c
	gcc -c test.c
clean:
	rm -f *.o *.so binary

