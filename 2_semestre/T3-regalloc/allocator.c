#include<limits.h>
#include<stdlib.h>
#include"allocator.h"
#include"graph.h"
#include"stack.h"

//retorna o índice da primeira ocorrencia do menor número no array (ignora negativos)
int min_in_array(int* array, int from, int to){
    int min       = INT_MAX;
    int min_index = 0;

    for(int i=from; i<to; i++){
        if(array[i] >=0 && array[i] < min){
            min = array[i];
            min_index = i;
        }
    }

    return min_index;
}
int max_in_array(int* array, int from, int to){
    int max       = INT_MIN;
    int max_index = 0;

    for(int i=from; i<to; i++){
        if(array[i] >=0 && array[i] > max){
            max = array[i];
            max_index = i;
        }
    }

    return max_index;
}

int potential_spill(Graph *graph, Stack *stack, int *edges_by_vertex){
    int max_index = max_in_array(edges_by_vertex, graph->first_register, graph->last_register+1);
    edges_by_vertex[max_index] = -1;
    vertex_colors[max_index] = SPILL;

    return max_index;
}

void simplify(Graph *grph, Stack *stck){
    int *edges_by_vertex = malloc( (grph->last_register + 1) * sizeof(int) );
    for(int i=grph->first_register; i < grph->last_register+1; i++){
        edges_by_vertex[i] = num_of_edges(*grph, i);
        printf("edges %2d: %2d\n", i, edges_by_vertex[i]);
    }

    for(int i=grph->first_register; i < grph->last_register+1; i++){
        int min_index = min_in_array(edges_by_vertex, grph->first_register, grph->last_register+1);

        if(edges_by_vertex[min_index] >= grph->max_colors){
            min_index = potential_spill(grph, stck, edges_by_vertex);
            printf("potspill %d\n", min_index); /* STDOUT */
        }else{
            printf("empilhou %d\n", min_index); /* STDOUT */
        }

        edges_by_vertex[min_index] = -1;
        *stck = push(*stck, grph->adjacency_matrix[min_index], min_index);
        *grph = remove_vertex(*grph, min_index);
    }

    free(edges_by_vertex);
}

int find_free_color(Graph graph, int from, int to, int vertex){
    int free_color = 0;

    for(int i=from; i<to; i++){
        if( is_edge(graph, i, vertex) ){
            if(vertex_colors[i] == free_color){
                free_color++;
                i = from;
            }
        }
    }

    return free_color;
}

void select_assign(Graph *graph, Stack *stack){
    int vertex;
    Adjacency adj;

    while( (adj = pop(stack, &vertex)) ){
        *graph = insert_vertex(*graph, vertex, adj);
        
        if(num_of_edges(*graph, vertex) >= graph->max_colors){
            printf("spill    %d\n", vertex); /* STDOUT */
            break;
        }

        int color = find_free_color(*graph, graph->first_register, graph->last_register+1, vertex);
        vertex_colors[vertex] = color;
        printf("assign   %d (%d)\n", vertex, color); /* STDOUT */
    }
}
