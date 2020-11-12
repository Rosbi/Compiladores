#include<stdio.h>
#include<math.h>
#include"calculus.h"

#define VIEW_WIDTH 80
#define VIEW_HEIGHT 25

typedef struct view_t{
    float x;
    float y;
    char pixel;
}View;

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

TreeNode function_g = NULL;
View screen[VIEW_WIDTH][VIEW_HEIGHT];

float riemannSum(TreeNode function, float lo_bound, float x_step);
void screenViewRatio(float *x_step, float *y_step);
void mergeFunctionToScreen(float *y_values);
void printScreen();

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

void plot(TreeNode function){
    if(!function){
        if(!function_g){ 
            printf("\n No Function defined!\n\n");
            return; 
        }
        function = function_g;
    }else{
        function_g = function;
    }

    // Array contendo a posição Y de para cada X do gráfico
    float y_values[VIEW_WIDTH];
    float x_step, y_step;
    int error = 0;
    screenViewRatio(&x_step, &y_step);

    for(int i=0;i<VIEW_WIDTH;i++){
        y_values[i] = solveForX(function, (h_view_lo + x_step*i), &error);
        if(error){
            printf("Houve um erro durante a avaliação da função passada, pedimos desculpas pelo incomodo\n");
            return;
        }
    }

    mergeFunctionToScreen(y_values);
    printScreen();
}

void functionGlobalDelete(){
    if(function_g){
        deleteTree(function_g);
    }
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
void screenViewRatio(float *x_step, float *y_step){
    *x_step = (h_view_hi - h_view_lo) / VIEW_WIDTH;
    *y_step = (v_view_hi - v_view_lo) / VIEW_HEIGHT;

    //Calcula a coordenada em cada pixel da tela, e torna o pixel vazio
    for(int i=0; i<VIEW_WIDTH; i++){
        for(int j=0; j<VIEW_HEIGHT; j++){
            screen[i][j].x = h_view_lo + (*x_step * i);
            screen[i][j].y = v_view_lo + (*y_step * j);
            screen[i][j].pixel = ' ';
        }
    }

    //Coloca o eixo na matriz, caso a opção esteja ligada
    if(draw_axis){
        float x_steps_to_zero = -1;
        float y_steps_to_zero = -1;
        //Eixo X
        if(v_view_lo * v_view_hi <= 0){
            y_steps_to_zero = v_view_lo / (v_view_hi - v_view_lo);
            y_steps_to_zero = floorf(fabsf(y_steps_to_zero * (VIEW_HEIGHT-1)));
            for(int i=0; i<VIEW_WIDTH; i++){
                screen[i][(int)y_steps_to_zero].pixel = '-';
            }
        }
        //Eixo Y
        if(h_view_lo * h_view_hi <= 0){
            x_steps_to_zero = h_view_lo / (h_view_hi - h_view_lo);
            x_steps_to_zero = floorf(fabsf(x_steps_to_zero * (VIEW_WIDTH-1)));
            for(int i=0; i<VIEW_HEIGHT; i++){
                screen[(int)x_steps_to_zero][i].pixel = '|';
            }
            //Intersecção dos dois eixos
            if(y_steps_to_zero != -1)
                { screen[(int)x_steps_to_zero][(int)y_steps_to_zero].pixel = '+'; }
        }
    }
}
void mergeFunctionToScreen(float *y_values){
    // float steps_to_y;
    // float range = v_view_hi - v_view_lo;
    int j;
    for(int i=0;i<VIEW_WIDTH;i++){
        if(y_values[i] >= v_view_lo && y_values[i] <= v_view_hi){
            // steps_to_y = fmodf(y_values[i], range) / range;
            // printf("y: % 2.3f | %%: %.6f | ", y_values[i], steps_to_y);
            // steps_to_y = roundf(fabsf(steps_to_y * VIEW_HEIGHT));
            // printf("offset: %.6f\n", steps_to_y);
            // screen[i][(int)steps_to_y].pixel = '*';
            
            // if(y_values[i] < screen[i][1].y){
            //     screen[i][0].pixel = '*';
            // }
            for(j=VIEW_HEIGHT-1;j>=0;j--){
                if(screen[i][j].y <= y_values[i]){
                    screen[i][j].pixel = '*';
                    break;
                }
            }
            // if(y_values[i] > screen[i][VIEW_HEIGHT-2].y){
            //     screen[i][j].pixel = '*';
            // }
        }
        
    }
}
void printScreen(){
    for(int y=VIEW_HEIGHT-1;y>=0;y--){
        for(int x=0;x<VIEW_WIDTH;x++){
            printf("%c", screen[x][y].pixel);
        }
        printf("\n");
    }
}
