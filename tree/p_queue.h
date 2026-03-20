#ifndef _P_QUEUE_H_
#define _P_QUEUE_H_

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
#endif // _P_QUEUE_H_