CC=gcc
CFLAGS= -c -std=c99

main: main.o lex_analyser.o parser.o stack.o globals.o custom_print.o
	$(CC) main.o lex_analyser.o parser.o stack.o globals.o custom_print.o -o main

main.o: main.c
	$(CC) main.c -o main.o $(CFLAGS)

lex_analyser.o: lex_analyser.c
	$(CC) lex_analyser.c -o lex_analyser.o $(CFLAGS)

parser.o: parser.c
	$(CC) parser.c -o parser.o $(CFLAGS)

stack.o: stack.c
	$(CC) stack.c -o stack.o $(CFLAGS)

globals.o: globals.c
	$(CC) globals.c -o globals.o $(CFLAGS)

custom_print.o: custom_print.c
	$(CC) custom_print.c -o custom_print.o $(CFLAGS)


clean:
	rm -rf *.o main