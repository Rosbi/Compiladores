#include<stdbool.h>
#include<stdio.h>
#include<stdint.h>
#include"afd.h"

const int estado_inicial=1;

const uint8_t simbolos[128] = 
{	//Tabela ascii

//	 0  1  2  3  4  5  6  7  8  9 
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

//	 10 11 12 13 14 15 16 17 18 19
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

//	20 21 22 23 24 25 26 27 28 29
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

//	30 31 ws  !  "  #  $  %  &  '
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

//	 (  )  *  +  ,  -  .  /  0  1
	 0, 0, 0, 1, 0, 2, 0, 0, 3, 4,

//	 2  3  4  5  6  7  8  9  :  ;
	 5, 6, 7, 8, 9,10,11,12, 0, 0,

//	 <  =  >  ?  @  A  B  C  D  E
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

//	 F  G  H  I  J  K  L  M  N  O
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

// 	 P  Q  R  S  T  U  V  W  X  Y
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

//	 Z  [  \  ]  ^  _  `  a  b  c
	 0, 0, 0, 0, 0, 0, 0,13, 0,14,

//	 d  e  f  g  h  i  j  k  l  m
	 0,15, 0, 0,16,17, 0, 0, 0, 0,

//	 n  o  p  q  r  s  t  u  v  w
	 0, 0, 0, 0,18,19,20, 0, 0, 0,

//	 x  y  z  {  |  }  ~ DEL
	 0, 0, 0, 0, 0, 0, 0, 0
};

const int8_t estados[state_quantity][symbol_quantity+1] =
{                  /* il  +  -  0  1  2  3  4  5  6  7  8  9  a  c  e  h  i  r  s  t */ 
	/* Estado  0 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	/* Estado  1 */	 { 0,17,18,19,19,19,19,19,19,19,19,19,19, 0,11, 0, 2, 0, 0, 4, 0}, 
	/* Estado  2 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 7, 0, 0, 0}, 
	/* Estado  3 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0}, 
	/* Estado  4 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0}, 
	/* Estado  5 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0}, 
	/* Estado  6 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	/* Estado  7 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0}, 
	/* Estado  8 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	/* Estado  9 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10, 0}, 
	/* Estado 10 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	/* Estado 11 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,12, 0, 0, 0, 0, 0, 0, 0}, 
	/* Estado 12 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,14, 0,13}, 
	/* Estado 13 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15, 0}, 
	/* Estado 14 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,16, 0}, 
	/* Estado 15 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	/* Estado 16 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	/* Estado 17 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	/* Estado 18 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	/* Estado 19 */	 { 0, 0, 0,19,19,19,19,19,19,19,19,19,19, 0, 0,20, 0, 0, 0, 0, 0}, 
	/* Estado 20 */	 { 0,21,21,22,22,22,22,22,22,22,22,22,22, 0, 0, 0, 0, 0, 0, 0, 0}, 
	/* Estado 21 */	 { 0, 0, 0,22,22,22,22,22,22,22,22,22,22, 0, 0, 0, 0, 0, 0, 0, 0}, 
	/* Estado 22 */	 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int selecionarPosicao(unsigned char caracter){
	return simbolos[caracter];
}

const char* eEstadoFinal(int estado){
	switch(estado){
		case  3:
			return "ELE";
		case  6:
			return "ELA";
		case  8:
			return "DELE";
		case 10:
			return "DELA";
		case 13:
			return "GATO";
		case 14:
			return "CARRO";
		case 15:
			return "GATOS";
		case 16:
			return "CARROS";
		case 17:
			return "MAIS";
		case 18:
			return "MENOS";
		case 19:
			return "INTEIRO";
		case 22:
			return "REAL";
		default:
		return NULL;
	}
}

void imprimirCadeia(int posicao_inicial, int posicao_final, FILE* input){
	char c;
	fseek(input, posicao_inicial, SEEK_SET);
	for(int i=posicao_inicial;i<posicao_final;i++){
		c = fgetc(input);
		if(c != '\n')
			printf("%c", c);
	}
}

void continuarLeitura(char input_atual, int *estado_atual, int *proximo_estado, int *c_posicao_atual, int *ultimo_final, int* c_ult_fin_recon){
	*estado_atual = *proximo_estado;
	(*c_posicao_atual)++;
	if(eEstadoFinal(*estado_atual)){
		*ultimo_final = *estado_atual;
		*c_ult_fin_recon = *c_posicao_atual;
	}
}

void reiniciarLeitura(char input_atual, int* ultimo_final, int* proximo_estado, int* estado_atual, int* c_inicio_leitura, int* c_posicao_atual,
						int* c_ult_fin_recon, FILE* input_file){
	const char* e_final = eEstadoFinal(*estado_atual);
	if(*ultimo_final==0 && e_final==NULL){
		if(input_atual != '\n')
			printf("%c ERRO\n", input_atual);
		(*c_inicio_leitura)++;
	}else if(*ultimo_final!=0 && e_final==NULL){
		imprimirCadeia(*c_inicio_leitura, *c_ult_fin_recon, input_file);
		printf(" %s\n", eEstadoFinal(*ultimo_final));
		*c_inicio_leitura = *c_ult_fin_recon;
	}else{
		imprimirCadeia(*c_inicio_leitura, *c_posicao_atual, input_file);
		printf(" %s\n", e_final);
		*c_inicio_leitura = *c_ult_fin_recon;
	}

	*c_posicao_atual = *c_inicio_leitura;
	*c_ult_fin_recon = *c_inicio_leitura;
	*estado_atual = estado_inicial;
	*ultimo_final = 0;
	fseek(input_file, *c_inicio_leitura, SEEK_SET);
}