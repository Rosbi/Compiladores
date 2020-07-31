#include<stdbool.h>
#include<stdio.h>
#include<stdint.h>
#include"afd.h"

const int estado_inicial=1;

const char simbolos[symbol_quantity] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g',
            'h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','.','-',' ','\n'};

const int8_t estados[14][symbol_quantity+1] =
{                 /* 0 1 2 3 4 5 6 7 8 9  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z .  - ' ' \n ot */ 
    /* Estado 00 */ {0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0,  0, 0, 0},
    /* Estado 01 */ {7,7,7,7,7,7,7,7,7,7, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,5, 9, 12, 0,13},
    /* Estado 02 */ {4,4,4,4,4,4,4,4,4,4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,0, 0,  0, 0, 0},
    /* Estado 03 */ {4,4,4,4,4,4,4,4,4,4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,0, 0,  0, 0, 0},
    /* Estado 04 */ {4,4,4,4,4,4,4,4,4,4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,0, 0,  0, 0, 0},
    /* Estado 05 */ {6,6,6,6,6,6,6,6,6,6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0,  0, 0, 0},
    /* Estado 06 */ {6,6,6,6,6,6,6,6,6,6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0,  0, 0, 0},
    /* Estado 07 */ {7,7,7,7,7,7,7,7,7,7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,8, 0,  0, 0, 0},
    /* Estado 08 */ {8,8,8,8,8,8,8,8,8,8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0,  0, 0, 0},
    /* Estado 09 */ {0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,10,  0, 0, 0},
    /* Estado 10 */ {0,0,0,0,0,0,0,0,0,0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0, 0,  0,11, 0},
    /* Estado 11 */ {0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0,  0, 0, 0},
    /* Estado 12 */ {0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 12, 0, 0},
    /* Estado 13 */ {0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0,  0, 0, 0},
};

int selecionarPosicao(char caracter){
    for(int i=0;i<symbol_quantity;i++){ if(simbolos[i]==caracter){return i;} }
    return -1;
}

const char* eEstadoFinal(int estado){
    switch(estado){
    case  2:
       return "ID";
    case  3:
       return "IF";
    case  4:
       return "ID";
    case  5:
       return "error";
    case  6:
       return "REAL";
    case  7:
       return "NUM";
    case  8:
       return "REAL";
    case  9:
       return "error";
    case 11:
        return "comment";
    case 12:
        return "white space";
    case 13:
       return "error";
    default:
       return NULL;
    }
}

void continuarLeitura(char input_atual, int *estado_atual, int *proximo_estado, int *c_posicao_atual, int *ultimo_final, int* c_ult_fin_recon){
    if(input_atual != '\n')
		printf("%c", input_atual);
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
    if(*ultimo_final==0 || e_final == NULL){
        if(input_atual != '\n')
			printf("%c error\n", input_atual);
        (*c_inicio_leitura)++;
    }else{
        printf(" %s\n", e_final);
        *c_inicio_leitura = *c_ult_fin_recon;
    }
    *c_posicao_atual = *c_inicio_leitura;
    *c_ult_fin_recon = *c_inicio_leitura;
    *estado_atual = estado_inicial;
    fseek(input_file, *c_inicio_leitura, SEEK_SET);
}