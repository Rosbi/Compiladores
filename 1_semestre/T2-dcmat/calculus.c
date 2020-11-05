#include<stdbool.h>
#include"calculus.h"

const float h_view_lo_default = -6.5;
const float h_view_hi_default =  6.5;
const float v_view_lo_default = -3.5;
const float v_view_hi_default =  3.5;
float h_view_lo = -6.5;
float h_view_hi =  6.5;
float v_view_lo = -3.5;
float v_view_hi =  3.5;
const bool draw_axis_default = true;
const bool connect_dots_default = false;
const int integral_steps_default = 1000;
int integral_steps = 1000;
bool draw_axis = true;
bool connect_dots = false;


void integralStepsSet(int intstps){
    integral_steps = intstps;
}
int integralStepsGet(){
    return integral_steps;
}
void integralStepsDefault(){
    integral_steps = integral_steps_default;
}
