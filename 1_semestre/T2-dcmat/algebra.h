#ifndef ALGEBRA_H
#define ALGEBRA_H

#include"abstractSyntaxTree.h"
#define MATRIX_MAX_SIZE 10

typedef void* Matrix;

/* Cria uma nova matriz a partir de uma arvore ast 
   Retorna NULL caso a quantidade de linhas ou colunas seja maior que MATRIX_MAX_SIZE */
Matrix matrixNew(TreeNode root);

/* Atribui a matriz m para a matriz interna do programa */
void matrixGlobalSet(Matrix);

/* Setters para diferentes atributos */
int matrixSetElement(Matrix mat, int row, int column, float num);
int matrixSetRows(Matrix mat, int rows);
int matrixSetColumns(Matrix mat, int columns);

/* Encontra o determinante da matriz m através da técnica de fatoração LU */
float matrixSolveDeterminant(Matrix m);

/* Encontra a matriz X solução da matriz M(n x n+1) */
void matrixSolveLinearSystem(Matrix m);

/* Imprime a matriz interna do programa na tela */
void matrixShow(Matrix);

/* Deleta a matriz passada */
void matrixDelete(Matrix);
void matrixGlobalDelete();

#endif