FLEX=flex
BISON=bison
CC=gcc
FLAGS=-g -Wall -std=c99

PROGRAMA = semantico
LEXICO = lexico.l
SEMANTICO = semantico.y

$(PROGRAMA): $(LEXICO) $(SEMANTICO)
	$(BISON) -d $(SEMANTICO)
	$(FLEX) $(LEXICO)
	$(CC) -c *.c -I. $(FLAGS)
	$(CC) *.o -o $(PROGRAMA) $(FLAGS)

clean:
	rm -f *.yy.c
	rm -f *.tab.c
	rm -f *.tab.h
	rm -f *.o
	rm -f *.exe
	rm -f semantico