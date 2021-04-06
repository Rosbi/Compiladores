#include<stdio.h>
#include"allocator.h"
#include"stack.h"
#include"graph.h"

int main(){
    // FILE* file_in = stdin;
    FILE* file_in = fopen("/home/sophie/Desktop/Compiladores/2_semestre/T3-regalloc/grafo.txt", "r");
    Graph graph = read_graph(file_in);
    Stack stack = create_stack();

    simplify(&graph, &stack);
    select_assign(&graph, &stack);

    // print_graph(graph);
    // print_stack(stack);
}
