#include<stdio.h>
#include"calculus.h"

float riemannSum(TreeNode function, float lo_bound, float x_step);

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

TreeNode function = NULL;

void showSettings(){
    printf("\n");
    printf(" h_view_lo: %.6f\n", h_view_lo);
    printf(" h_view_hi: %.6f\n", h_view_hi);
    printf(" v_view_lo: %.6f\n", v_view_lo);
    printf(" v_view_hi: %.6f\n", v_view_hi);
    printf(" integral_steps: %d\n", integral_steps);
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
    if(lo >= hi){
        printf("\nError: h_view_lo must be smaller than h_view_hi\n\n");
        return;
    }

    h_view_lo = lo;
    h_view_hi = hi;
}
void setVView(float lo, float hi){
    if(lo >= hi){
        printf("\nError: v_view_lo must be smaller than v_view_hi\n\n");
        return;
    }

    v_view_lo = lo;
    v_view_hi = hi;
}
void integralStepsSet(int intstps){
    if(intstps <= 0){
        printf("\nERROR: integral_steps must be a positive non-zero integer\n\n");
        return;
    }
    integral_steps = intstps;
}
void setAxis(bool axis){
    draw_axis = axis;
}

void integrate(TreeNode function, float inf_limit, float sup_limit){
    if(!function){ 
        printf("\nError: no function passed\n\n");
        return;
    }

    if(inf_limit > sup_limit){
        printf("\nERROR: lower limit must be smaller than upper limit\n\n");
        return;
    }else if(inf_limit == sup_limit){
        printf("\n%f\n\n", 0.0);
        return;
    }

    float x_interval = (sup_limit - inf_limit) / integral_steps;
    float result = riemannSum(function, inf_limit, x_interval);
    printf("\n%f\n\n", result);
}

/* funções auxiliares */
float riemannSum(TreeNode function, float lo_bound, float x_step){
    float x = lo_bound, height, sum = 0;
    int error = 0;
    for(int i = 0; i < integral_steps; i++, x+=x_step){
        height = solveForX(function, (x+(x_step/2)), &error);
        // printf("f(%f) -> %f\n", x, height);
        if(error){
            printf("\nThere was an error with the Riemann Sum, we are sorry for the inconvenient\n\n");
            return 0.0;
        }
        sum += height;
    }
    return sum * x_step;
}

void functionGlobalDelete(){
    if(function){
        deleteTree(function);
    }
}
