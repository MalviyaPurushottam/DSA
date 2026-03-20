#ifndef _P_QUEUE_H_
#define _P_QUEUE_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int data;
} node_t;

typedef struct QueueNode_t{
    int data;  // this can be replaced by data structure
    struct QueueNode_t* nxt_link;
}QueueNode;

typedef struct Queue_t{
    QueueNode* head;
    QueueNode* tail;
} Queue;

Queue* Queue_create(void);
Queue* EnQueue(Queue* q, int data);
Queue* DeQueue(Queue* q);
int Queue_front(Queue* q);
int Queue_size(Queue* q);
bool Queue_isEmpty(Queue* q);

void Queue_print(Queue* q);

#endif // _P_QUEUE_H_