#include<stdlib.h>
#include"algebra.h"

typedef struct matrix{
    float **m;
    int rows;
    int columns;
}matrix_t;

matrix_t *matrix_g = NULL;

void matrixNew(float **matrix_p, int rows, int columns){
    if(!matrix_g){
        matrix_g = malloc(sizeof(matrix_t));
    }else{
        free(matrix_g->m);
    }

    matrix_g->m = matrix_p;
    matrix_g->rows = rows;
    matrix_g->columns = columns;

}
