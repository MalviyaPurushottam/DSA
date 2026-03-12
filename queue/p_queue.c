#include "p_queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Queue* Queue_create(void){

    Queue* q = (Queue*)malloc(sizeof(Queue));
    
    // init the head and tail to null
    q->head = NULL;
    q->tail = NULL;

    return q;
}

Queue* EnQueue(Queue* q, int data){
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));

    node->data = data;
    node->nxt_link = NULL;
    // if the node is the first node to be inserted
    if(q->head == NULL){
        q->head = node;
        q->tail = node;
    }
    else{
        // tail will always point to the last node and next link in last node will point to null
        q->tail->nxt_link = node;
        q->tail = node;
    }

    return q;
}

Queue* DeQueue(Queue* q){
    if(q->head == NULL){
        return q;
    }

    QueueNode* temp = q->head;
    q->head = q->head->nxt_link;
    free(temp);

    return q;
}

int Queue_front(Queue* q){
    if(q->head == NULL){
        return -1;
    }
    return q->head->data;
}

int Queue_size(Queue* q){
    int count = 0;

    QueueNode* temp = q->head;
    while(temp!=NULL){
        temp = temp->nxt_link;
        count++;
    }
    
    return count;
}

bool Queue_isEmpty(Queue* q){
    // if any of head or tail point to NULL then queue is broken
    if((q->head == NULL) || (q->tail == NULL)){
        return true;
    }
    return false;
}

void Queue_print(Queue* q){
    QueueNode* temp = q->head;
    printf("Now printing the queue\nHEAD -> ");
    while(temp!=NULL){
        printf("%d -> ", temp->data);
        temp = temp->nxt_link;
    }
    printf("TAIL\n");
    return;
}