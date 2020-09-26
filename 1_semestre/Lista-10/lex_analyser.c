#include<stdbool.h>
#include<stdio.h>
#include<stdint.h>
#include<ctype.h>
#include<string.h>
#include"lex_analyser.h"

const int estado_inicial=1;

const int symbol_quantity = 3 + 6;
const int state_quantity  = 3 + 41;

const uint8_t simbolos[128] = 
{
//			Tabela ascii
//	 0  1  2  3  4  5  6  7  8  9 
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,

//	\n 11 12 13 14 15 16 17 18 19
	 2, 1, 1, 1, 0, 0, 0, 0, 0, 0,

//	20 21 22 23 24 25 26 27 28 29
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

//	30 31 ws  !  "  #  $  %  &  '
	 0, 0, 1, 0, 0, 0,43, 0, 0, 0,

//	 (  )  *  +  ,  -  .  /  0  1
	 3, 4, 5, 6, 0, 0, 0, 0, 7, 8,

//	 2  3  4  5  6  7  8  9  :  ;
	 9,10,11,12,13,14,15,16, 0, 0,

//	 <  =  >  ?  @  A  B  C  D  E
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

//	 F  G  H  I  J  K  L  M  N  O
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

// 	 P  Q  R  S  T  U  V  W  X  Y
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

//	 Z  [  \  ]  ^  _  `  a  b  c
	 0, 0, 0, 0, 0, 0, 0,17,18,19,

//	 d  e  f  g  h  i  j  k  l  m
	20,21,22,23,24,25,26,27,28,29,

//	 n  o  p  q  r  s  t  u  v  w
	30,31,32,33,34,35,36,37,38,39,

//	 x  y  z  {  |  }  ~ DEL
	40,41,42, 0, 0, 0, 0, 0
};

const int8_t estados[state_quantity][symbol_quantity] =
{          /* il  ws \n (  )  *  +  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  $ */ 
	/* 00 */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //Ilegal
	/* 01 */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //whitespaces
	/* 02 */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //\n

	/* 03 */ { 0, 1, 2, 6, 7, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9}, //inicial
	/* 04 */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //PLUS_SIGN
	/* 05 */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //MULT_SIGN
	/* 06 */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //LPAREN
	/* 07 */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //RPAREN
	/* 08 */ { 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0}, //ID
	/* 09 */ { 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0}, //DOLLAR
};

char* tokenStringify(token_type token){
	switch(token){
		case TOKEN_ERROR:	return "erro";
		case WHITESPACE:	return "whitespace";
		case PLUS_SIGN:		return "+";
		case MULT_SIGN:		return "*";
		case LPAREN:		return "(";
		case RPAREN:		return ")";
		case ID:			return "id";
		case DOLLAR:		return "dollar";
		default:			return "this should not be possible";
	}
}

int selecionarPosicao(unsigned char caracter){
	return simbolos[caracter];
}

token_type getEstado(int estado){
	switch(estado){
		case 1: return WHITESPACE;
		case 2: return NEWLINE;
		case 4: return PLUS_SIGN;
		case 5: return MULT_SIGN;
		case 6: return LPAREN;
		case 7: return RPAREN;
		case 8: return ID;
		case 9: return DOLLAR;
		default: return TOKEN_ERROR;
	}
}

/*
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
*/

void continuarLeitura(char input_atual, int *estado_atual, int *proximo_estado, int *c_posicao_atual, int *ultimo_final, int* c_ult_fin_recon){
	*estado_atual = *proximo_estado;
	(*c_posicao_atual)++;
	if(getEstado(*estado_atual) != TOKEN_ERROR){
		*ultimo_final = *estado_atual;
		*c_ult_fin_recon = *c_posicao_atual;
	}
}

token_type reiniciarLeitura(char input_atual, int* ultimo_final, int* proximo_estado, int* estado_atual, int* c_inicio_leitura, int* c_posicao_atual,
						int* c_ult_fin_recon, FILE* input_file){
	token_type token = getEstado(*estado_atual);
	
	//Cadeia reconhecida, cursor em estado final
	if(*ultimo_final != 0 && token != TOKEN_ERROR){
		*c_inicio_leitura = *c_posicao_atual;
	}
	//Cadeia reconhecida, mas cursor em estado não final
	else if(*ultimo_final!=0 && token==TOKEN_ERROR){
		token = getEstado(*c_ult_fin_recon);
		*c_inicio_leitura = *c_ult_fin_recon;
	}
	//cadeia não reconhecida
	else{
		(*c_inicio_leitura)++;
	}
	
	if(input_atual != EOF){
		fseek(input_file, *c_inicio_leitura, SEEK_SET);
	}

	return token;
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
		
		if(feof(file_in)){
			return TOKEN_ERROR;
		}
	}
}
