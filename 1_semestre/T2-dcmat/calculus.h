#ifndef CALCULUS_H
#define CALCULUS_H

#include<stdbool.h>
#include"abstractSyntaxTree.h"

void showSettings();
void resetSettings();
void setHView(float, float);
void setVView(float, float);
void integralStepsSet(int);
void setAxis(bool);

/* calcula a integral definida da função, utilizando a soma de Riemann (ponto médio) */
void integrate(TreeNode function, float inf_limit, float sup_limit);

void plot(TreeNode function);

void functionGlobalDelete();

#endif