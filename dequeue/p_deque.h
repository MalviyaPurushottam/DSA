#ifndef _P_DEQUE_H_
#define _P_DEQUE_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct node_t{
    int data;
} node;

typedef struct deque_node_t{
    node node;
    struct deque_node_t* nxt;
    struct deque_node_t* prev;
} deque_node;

typedef struct deque_t{
    deque_node* first;
    deque_node* last;
} Deque;


Deque* Deque_create(void);
void Deque_delete(Deque* d);

Deque* Deque_insertFirst(Deque* d, node* data);
Deque* Deque_insertLast(Deque* d, node* data);
Deque* Deque_removeFirst(Deque* d);
Deque* Deque_removeLast(Deque* d);
node* Deque_first(Deque* d);
node* Deque_last(Deque* d);

int Deque_size(Deque* d);
void Deque_printFromStart(Deque* d);
void Deque_printFromLast(Deque* d);

#endif