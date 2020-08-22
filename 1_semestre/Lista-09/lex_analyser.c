#include<stdbool.h>
#include<stdio.h>
#include<stdint.h>
#include<ctype.h>
#include<string.h>
#include"lex_analyser.h"

const int estado_inicial=1;

const uint8_t simbolos[128] = 
{
//			Tabela ascii
//	 0  1  2  3  4  5  6  7  8  9 
	 0, 0, 0, 0, 0, 0, 0, 0, 0,28,

//	10 11 12 13 14 15 16 17 18 19
	28,28,28,28, 0, 0, 0, 0, 0, 0,

//	20 21 22 23 24 25 26 27 28 29
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

//	30 31 ws  !  "  #  $  %  &  '
	 0, 0,28, 0, 0, 0, 0, 0, 0, 0,

//	 (  )  *  +  ,  -  .  /  0  1
	 0, 0, 0, 1, 0, 2, 0, 0, 3, 4,

//	 2  3  4  5  6  7  8  9  :  ;
	 5, 6, 7, 8, 9,10,11,12, 0,26,

//	 <  =  >  ?  @  A  B  C  D  E
	 0,27, 0, 0, 0, 0, 0, 0, 0, 0,

//	 F  G  H  I  J  K  L  M  N  O
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

// 	 P  Q  R  S  T  U  V  W  X  Y
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

//	 Z  [  \  ]  ^  _  `  a  b  c
	 0, 0, 0, 0, 0, 0, 0, 0,13, 0,

//	 d  e  f  g  h  i  j  k  l  m
	14,15,16,17,18,19, 0, 0,20, 0,

//	 n  o  p  q  r  s  t  u  v  w
	21, 0,22, 0,23,24,25, 0, 0, 0,

//	 x  y  z  {  |  }  ~ DEL
	 0, 0, 0, 0, 0, 0, 0, 0
};

const int8_t estados[state_quantity+2][symbol_quantity+2] =
{                  /* il  +  -  0  1  2  3  4  5  6  7  8  9  b  d  e  f  g  h  i  l  n  p  r  s  t  ;  = ws */ 
	/* Estado  0 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	/* Estado  1 */	 { 0,24,24,25,25,25,25,25,25,25,25,25,25,12, 0, 8, 0, 0, 0, 2, 0, 0,19, 0, 0, 4,27,26,28},
	/* Estado  2 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	/* Estado  3 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //final
	/* Estado  4 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	/* Estado  5 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	/* Estado  6 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0},
	/* Estado  7 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //final
	/* Estado  8 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,17, 0, 0, 0, 0, 0, 0, 0},
	/* Estado  9 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10, 0, 0, 0, 0},
	/* Estado 10 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	/* Estado 11 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //final
	/* Estado 12 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	/* Estado 13 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	/* Estado 14 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	/* Estado 15 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,16, 0, 0, 0, 0, 0, 0, 0},
	/* Estado 16 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //final
	/* Estado 17 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	/* Estado 18 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //final
	/* Estado 19 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20, 0, 0, 0, 0, 0},
	/* Estado 20 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,21, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	/* Estado 21 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,22, 0, 0, 0, 0, 0, 0, 0},
	/* Estado 22 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,23, 0, 0, 0},
	/* Estado 23 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //final
	/* Estado 24 */	 { 0, 0, 0,25,25,25,25,25,25,25,25,25,25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	/* Estado 25 */	 { 0, 0, 0,25,25,25,25,25,25,25,25,25,25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //final
	/* Estado 26 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //final
	/* Estado 27 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //final
	/* Estado 28 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //estado whitespaces
};

int selecionarPosicao(unsigned char caracter){
	return simbolos[caracter];
}

token_type eEstadoFinal(int estado){
	switch(estado){
		case  3: return IF;
		case  7: return THEN;
		case 11: return ELSE;
		case 16: return BEGIN;
		case 18: return END;
		case 23: return PRINT;
		case 25: return NUMBER;
		case 26: return EQUALS;
		case 27: return SEMICOLON;
        case 28: return WHITESPACE;
		default: return TOKEN_ERROR;
	}
}

void imprimirCadeia(int posicao_inicial, int posicao_final, FILE* input){
	char c;
	fseek(input, posicao_inicial, SEEK_SET);
	printf(" ");
	for(int i=posicao_inicial;i<posicao_final;i++){
		c = fgetc(input);
		if(c != '\n' && c != EOF && c != ' ')
			printf("%c", c);
	}
}

void continuarLeitura(char input_atual, int *estado_atual, int *proximo_estado, int *c_posicao_atual, int *ultimo_final, int* c_ult_fin_recon){
	*estado_atual = *proximo_estado;
	(*c_posicao_atual)++;
	if(eEstadoFinal(*estado_atual) != TOKEN_ERROR){
		*ultimo_final = *estado_atual;
		*c_ult_fin_recon = *c_posicao_atual;
	}
}

token_type reiniciarLeitura(char input_atual, int* ultimo_final, int* proximo_estado, int* estado_atual, int* c_inicio_leitura, int* c_posicao_atual,
						int* c_ult_fin_recon, FILE* input_file){
	token_type e_final = eEstadoFinal(*estado_atual);
	
    //Cadeia reconhecida, cursor em estado final
    if(*ultimo_final != 0 && e_final != TOKEN_ERROR){
        *c_inicio_leitura = *c_posicao_atual;
    }
	//Cadeia reconhecida, mas cursor em estado não final
	else if(*ultimo_final!=0 && e_final==TOKEN_ERROR){
		e_final = eEstadoFinal(*c_ult_fin_recon);
        *c_inicio_leitura = *c_ult_fin_recon;
	}
    //cadeia não reconhecida
    else{
        (*c_inicio_leitura)++;
    }
    
	// *c_posicao_atual = *c_inicio_leitura;
	// *c_ult_fin_recon = *c_inicio_leitura;
	// *estado_atual = estado_inicial;
	// *ultimo_final = 0;
    if(input_atual != EOF){
	    fseek(input_file, *c_inicio_leitura, SEEK_SET);
    }/*
    else{
        fseek(input_file, 0, SEEK_END);
        getc(input_file);
    }*/

    return e_final;
}

token_type getToken(FILE* file_in){
    int estado_atual     = estado_inicial;
	int ultimo_final     = 0;
	int c_inicio_leitura = 0;
	static int c_posicao_atual  = 0;
	int c_ult_fin_recon  = 0;
	char input_atual     = '\0';

	while(true){
		input_atual = fgetc(file_in);

		int proximo_estado = estados[estado_atual][selecionarPosicao(input_atual)];
		if(proximo_estado==0){
			return reiniciarLeitura(input_atual, &ultimo_final, &proximo_estado, &estado_atual, &c_inicio_leitura, &c_posicao_atual, &c_ult_fin_recon, file_in);
		}else{
			continuarLeitura(input_atual, &estado_atual, &proximo_estado, &c_posicao_atual, &ultimo_final, &c_ult_fin_recon);
		}
	}
}
