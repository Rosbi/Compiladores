#include"globals.h"

FILE* file_in = NULL;
Stack stck = NULL;

int linha  = 1;
int coluna = 1;

int getLinha(){
    return linha;
}
void setLinha(int i){
    linha = i;
}
int getColuna(){
    return coluna;
}
void setColuna(int i){
    coluna = i;
}
