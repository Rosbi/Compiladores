#include<stdbool.h>
#include<stdio.h>
#include"afd.h"

const int estado_inicial=1;

const char simbolos[symbol_quantity] = {'+','-','0','1','2','3','4','5','6','7','8','9','a','b','c',
    'd','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','\n'};

const int estados[9][symbol_quantity+1] =
{                /* + - 0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p q r s t u v w x y z \n erro*/ 
    /* Estado 0 */ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
    /* Estado 1 */ {3,4,5,5,5,5,5,5,5,5,5,5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,-1},
    /* Estado 2 */ {0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,-1},
    /* Estado 3 */ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,-1},
    /* Estado 4 */ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,-1},
    /* Estado 5 */ {0,0,5,5,5,5,5,5,5,5,5,5,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,-1},
    /* Estado 6 */ {7,7,8,8,8,8,8,8,8,8,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,-1},
    /* Estado 7 */ {0,0,8,8,8,8,8,8,8,8,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,-1},
    /* Estado 8 */ {0,0,8,8,8,8,8,8,8,8,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,-1},
};

int selecionarPosicao(char caracter){
  for(int i=0;i<symbol_quantity;i++){ 
    if(simbolos[i]==caracter){
      return i;} }
  return -1;
}

bool eEstadoFinal(int estado){

  /*
  switch(estado){
  case 2:
  case 3:
  case 4:
  case 5:
  case 8:
    return true;
  default:
    return false;
  }
  */
  if(  estado == 2
    || estado == 3
    || estado == 4
    || estado == 5
    || estado == 8
  ) return true;
  else return false;
}

void continuarLeitura(char *input_atual, int *estado_atual, int *proximo_estado, int *c_posicao_atual,
                        int *ultimo_final, int* c_ult_fin_recon){
    printf("%c", *input_atual);
    *estado_atual = *proximo_estado;
    (*c_posicao_atual)++;
    if(eEstadoFinal(*estado_atual)){
        *ultimo_final = *estado_atual;
        *c_ult_fin_recon = *c_posicao_atual;
    }
}

void reiniciarLeitura(int* ultimo_final, int* proximo_estado, int* estado_atual, int* c_inicio_leitura,
                        int* c_posicao_atual, int* c_ult_fin_recon, FILE* input_file){
    if(*ultimo_final==0 || !eEstadoFinal(*estado_atual)){
        printf("ERRO\n");
        (*c_inicio_leitura)++;
    }else{
        printf("\n");
        *c_inicio_leitura = *c_ult_fin_recon;
    }
    *c_posicao_atual = *c_inicio_leitura;
    *c_ult_fin_recon = *c_inicio_leitura;
    *estado_atual = estado_inicial;
    fseek(input_file, *c_inicio_leitura, SEEK_SET);
}