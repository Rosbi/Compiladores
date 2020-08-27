main: main.o lex_analyser.o
	gcc main.o lex_analyser.o -o main

main.o: main.c
	gcc main.c -o main.o -c

lex_analyser.o: lex_analyser.c
	gcc lex_analyser.c -o lex_analyser.o -c

clean:
	rm -rf *.o main