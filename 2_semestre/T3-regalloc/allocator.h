#ifndef REGISTER_ALLOCATOR_H
#define REGISTER_ALLOCATOR_H

#include"graph.h"
#include"stack.h"

void simplify(Graph*, Stack*);
void select_assign(Graph*, Stack*);

#endif
