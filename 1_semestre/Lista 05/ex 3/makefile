main: main.o afd.o
	gcc main.o afd.o -o main

main.o: main.c afd.h
	gcc main.c -o main.o -c

afd.o: afd.c afd.h
	gcc afd.c -o afd.o -c


clean:
	rm -rf main *.o