#ifndef CALCULUS_H
#define CALCULUS_H

#include<stdbool.h>

void showSettings();
void resetSettings();
void setHView(float, float);
void setVView(float, float);
void integralStepsSet(int);
// int integralStepsGet();
void setAxis(bool);

/*
set_h_view(float, float)
set_v_view(float, float)
set_axis(bool)
plot(expression)
-- rpn_impression
integrate(expression)
*/

#endif