main: main.o lex_analyser.o
	gcc main.o lex_analyser.o parser.o stack.o -o main

main.o: main.c
	gcc main.c -o main.o -c

lex_analyser.o: lex_analyser.c
	gcc lex_analyser.c -o lex_analyser.o -c

parser.o: parser.c
	gcc parser.c -o parser.o -c

stack.o: stack.o
	gcc stack.c -o stack.o -c

clean:
	rm -rf *.o main