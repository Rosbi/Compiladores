main: main.o graph.o allocator.o stack.o
	gcc main.o graph.o allocator.o stack.o -o main

main.o: main.c
	gcc main.c -o main.o -c -std=c99 -Wall

allocator.o: allocator.c
	gcc allocator.c -o allocator.o -c -std=c99 -Wall

graph.o: graph.c
	gcc graph.c -o graph.o -c -std=c99 -Wall

stack.o: stack.c
	gcc stack.c -o stack.o -c -std=c99 -Wall

clean:
	rm -rf main *.o
cleantxt:
	rm -rf *.txt