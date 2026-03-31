#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>


typedef struct q_node_t{
    void* node_ptr;
    struct q_node_t* nxt;
} q_node;

typedef struct{
    q_node* head;
    q_node* tail;
} queue;

queue* Q_create(void);
void Q_enqueue(queue* Q, void* node);
void* Q_dequeue(queue* Q);

int Q_isEmpty(queue* Q);
int Q_size(queue* Q);

#endif // QUEUE_H
