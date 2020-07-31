#ifndef CONST_H
#define CONST_H

#include<stdio.h>

#define symbol_quantity 39

extern const int estado_inicial;

extern const char simbolos[symbol_quantity];

extern const int estados[9][symbol_quantity+1];

int selecionarPosicao(char caracter);
bool eEstadoFinal(int estado);

void continuarLeitura(char *input_atual, int *estado_atual, int *proximo_estado, int *c_posicao_atual,
                        int *ultimo_final, int* c_ult_fin_recon);

void reiniciarLeitura(int* ultimo_final, int* proximo_estado, int* estado_atual, int* c_inicio_leitura,
                        int* c_posicao_atual, int* c_ult_fin_recon, FILE* input_file);

#endif