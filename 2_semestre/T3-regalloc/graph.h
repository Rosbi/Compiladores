#ifndef GRAPH_H
#define GRAPH_H

#define NO_EDGE 0
#define IS_EDGE 1

typedef int* Adjacency;

typedef struct{
    char graph_name[10];
    Adjacency *adjacency_matrix;
    int max_colors;
    int first_register;
    int last_register;
}Graph;

Graph read_graph(FILE* file_in);
bool is_edge(Graph g, int v1, int v2);
void remove_vertex(Graph g, int v);
void insert_vertex(Graph g, int v, Adjacency adj);

#endif
