#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include"graph.h"

#define LINE_MAX 300

static Adjacency null_adjacency;
static int* vertex_colors;

Graph read_graph(FILE* file_in){
    char line_in[LINE_MAX];
    Graph g;

    //Lê o nome do grafo
    fgets(line_in, LINE_MAX, file_in);
    sscanf(line_in, "%*s %s", g.graph_name);
    g.graph_name[strlen(g.graph_name)-1] = '\0';
    
    //Lê a quantidade de cores K
    fgets(line_in, LINE_MAX, file_in);
    sscanf(line_in, "%*c%*c%d", &g.max_colors);

    //Lê o primeiro registrador virtual
    long graph_start = ftell(file_in);
    fgets(line_in, LINE_MAX, file_in);
    sscanf(line_in, "%d", &g.first_register);

    //Lê o último registrador virtual
    do{
        fgets(line_in, LINE_MAX, file_in);
        sscanf(line_in, "%d", &g.last_register);
    }while(!feof(file_in));
    fseek(file_in, graph_start, SEEK_SET);

    //Aloca a matriz de adjacência
    g.adjacency_matrix = malloc( ( g.last_register + 1 ) * sizeof(int*) );
    for(int i=0; i<g.last_register; i++){
        g.adjacency_matrix[i] = malloc( ( g.last_register + 1) * sizeof(int) );
    }
    for(int i=0; i<g.last_register; i++){
        for(int j=0; j<g.last_register; j++){
            g.adjacency_matrix[i][j] = NO_EDGE;
        }
    }

    //Insere os valores na matriz
    while(fgets(line_in, LINE_MAX, file_in), !feof(file_in)){
        int vertex;
        sscanf(line_in, "%d", &vertex);
        char *str = line_in + 5;
        while(*str && *str != '\n'){
            if( isdigit(*str) ){
                long edge = strtol(str, &str, 10);
                g.adjacency_matrix[vertex][edge] = IS_EDGE;
            }else{
                str++;
            }
        }
    }

    null_adjacency = malloc( (g.last_register + 1) * sizeof(int) );
    vertex_colors = malloc( (g.last_register + 1) * sizeof(int) );
    for(int i=0;i<g.last_register+1;i++){
        null_adjacency[i] =  0;
        vertex_colors[i]  = -1;
    }

    /*
    printf("%s\n%d\n%d\n%d\n", g.graph_name, g.max_colors, g.first_register, g.last_register);
    for(int i=0; i<g.last_register; i++){
        for(int j=0; j<g.last_register; j++){
            printf("%d ", g.adjacency_matrix[i][j]);
        }
        printf("\n");
    }
    */

    return g;
}

bool is_edge(Graph g, int v1, int v2){
    if(v1 >= g.last_register || v2 >= g.last_register){
        return false;
    }

    if(g.adjacency_matrix[v1][v2] != NO_EDGE){
        return true;
    }else{
        return false;
    }
}

void remove_vertex(Graph g, int v){
    if(v >= g.last_register){
        return;
    }

    g.adjacency_matrix[v] = null_adjacency;
}

void insert_vertex(Graph g, int v, Adjacency adj){
    if(v >= g.last_register){
        return;
    }

    g.adjacency_matrix[v] = adj;
}

int num_of_edges(Graph g, int v){
    if(v >= g.last_register){
        return -1;
    }

    int edge_count = 0;
    for(int i=0; i < g.last_register+1; i++){
        if(g.adjacency_matrix[v][i] == IS_EDGE){
            edge_count++;
        }
    }

    return edge_count;
}

// int main(){
//     FILE* file_in = stdin;
//     // FILE* file_in = fopen("/home/sophie/Desktop/Compiladores/2_semestre/T3-regalloc/grafo.txt", "r");
//     Graph g = read_graph(file_in);

//     return 0;
// }
