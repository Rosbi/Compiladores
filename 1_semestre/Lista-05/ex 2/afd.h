#ifndef CONST_H
#define CONST_H

#include<stdio.h>
#include<stdint.h>

#define symbol_quantity 40

extern const int estado_inicial;

extern const char simbolos[symbol_quantity];

extern const int8_t estados[14][symbol_quantity+1];

int selecionarPosicao(char caracter);
const char* eEstadoFinal(int estado);

void continuarLeitura(char input_atual, int *estado_atual, int *proximo_estado, int *c_posicao_atual,
                        int *ultimo_final, int* c_ult_fin_recon);

void reiniciarLeitura(char input_atual, int* ultimo_final, int* proximo_estado, int* estado_atual,
						int* c_inicio_leitura, int* c_posicao_atual, int* c_ult_fin_recon, FILE* input_file);

#endif