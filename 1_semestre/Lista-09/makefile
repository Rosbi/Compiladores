l9e1: main.o lex_analyser.o
	gcc main.o lex_analyser.o -o l9e1

main.o: main.c
	gcc main.c -o main.o -c

lex_analyser.o: lex_analyser.c
	gcc lex_analyser.c -o lex_analyser.o -c

clean:
	rm -rf *.o l9e1
