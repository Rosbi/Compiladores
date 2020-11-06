#include<stdio.h>
#include"calculus.h"

const float h_view_lo_default    = -6.5;
const float h_view_hi_default    =  6.5;
const float v_view_lo_default    = -3.5;
const float v_view_hi_default    =  3.5;
const int integral_steps_default = 1000;
const bool connect_dots_default  = false;
const bool draw_axis_default     = true;
float h_view_lo    = -6.5;
float h_view_hi    =  6.5;
float v_view_lo    = -3.5;
float v_view_hi    =  3.5;
int integral_steps = 1000;
bool connect_dots  = false;
bool draw_axis     = true;

void showSettings(){
    printf("\n");
    printf(" h_view_lo: %.6f\n", h_view_lo);
    printf(" h_view_hi: %.6f\n", h_view_hi);
    printf(" v_view_lo: %.6f\n", v_view_lo);
    printf(" v_view_hi: %.6f\n", v_view_hi);
    printf(" \n");
    printf(" Draw axis: %s", draw_axis ? "ON\n" : "OFF\n");
    printf(" Connect dots: %s", connect_dots ? "ON\n" : "OFF\n");
    printf("\n");
}
void resetSettings(){
    h_view_lo = h_view_lo_default;
    h_view_hi = h_view_hi_default;
    v_view_lo = v_view_lo_default;
    v_view_hi = v_view_hi_default;
    draw_axis = draw_axis_default;
    connect_dots = connect_dots_default;
    integral_steps = integral_steps_default;
}
void setHView(float lo, float hi){
    if(lo < hi){
        h_view_lo = lo;
        h_view_hi = hi;
    }
}
void setVView(float lo, float hi){
    if(lo < hi){
        v_view_lo = lo;
        v_view_hi = hi;
    }
}
void integralStepsSet(int intstps){
    integral_steps = intstps;
}
// int integralStepsGet(){
//     return integral_steps;
// }
void setAxis(bool axis){
    draw_axis = axis;
}

