#ifndef CONST_H
#define CONST_H

#include<stdio.h>
#include<stdint.h>

#define symbol_quantity 27
#define state_quantity 27

typedef int token_type;
enum tokens{
    TOKEN_ERROR,
    IF,
    THEN,
    ELSE,
    BEGIN,
    END,
    PRINT,
    SEMICOLON,
    NUMBER,
    EQUALS,
    WHITESPACE
};
/*
extern const int estado_inicial;

extern const uint8_t simbolos[128];

extern const int8_t estados[state_quantity+1][symbol_quantity+1];
/*
int selecionarPosicao(unsigned char caracter);
int eEstadoFinal(int estado);

void continuarLeitura(char input_atual, int *estado_atual, int *proximo_estado, int *c_posicao_atual,
                        int *ultimo_final, int* c_ult_fin_recon);

token_type reiniciarLeitura(char input_atual, int* ultimo_final, int* proximo_estado, int* estado_atual,
						int* c_inicio_leitura, int* c_posicao_atual, int* c_ult_fin_recon, FILE* input_file);
*/
token_type getToken();

#endif