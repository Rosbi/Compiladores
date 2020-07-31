#include<stdbool.h>
#include<stdio.h>
#include<stdint.h>
#include"afd.h"

const int estado_inicial=1;

const char simbolos[symbol_quantity] = {'a','b'};

const int8_t estados[state_quantity][symbol_quantity+1] =
{                 	/* a  b il */ 
	/* Estado  0 */	 { 0, 0, 0}, 
	/* Estado  1 */	 { 2, 3, 0}, 
	/* Estado  2 */	 { 4, 5, 0}, 
	/* Estado  3 */	 { 0, 0, 0}, 
	/* Estado  4 */	 { 0, 0, 0}, 
	/* Estado  5 */	 { 6, 7, 0}, 
	/* Estado  6 */	 { 0, 8, 0}, 
	/* Estado  7 */	 { 4, 7, 0}, 
	/* Estado  8 */	 { 0, 9, 0}, 
	/* Estado  9 */	 {10, 0, 0}, 
	/* Estado 10 */	 { 0, 8, 0},		
};

int selecionarPosicao(char caracter){
    for(int i=0;i<symbol_quantity;i++){ if(simbolos[i]==caracter){return i;} }
    return -1;
}

const char* eEstadoFinal(int estado){
    switch(estado){
    case  2:
    	return "(action 3)";
    case  3:
    	return "(action 3)";
    case  4:
    	return "(action 2)";
    case  6:
    	return "(action 1)";
    case 10:
    	return "(action 1)";
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
    //if(input_atual != '\n')
		//printf("%c", input_atual);
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
			printf("%c error\n", input_atual);
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