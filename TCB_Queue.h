
#ifndef TCB_QUEUE_H
#define	TCB_QUEUE_H

#define NO_ERROR 0
#define ERROR -1
#include "TCB.h"

struct TCB_queue_node_struct {
    struct TCB_struct* data;
    struct TCB_queue_node_struct* next;
};

struct TCB_queue_struct {
    int count;
    struct TCB_queue_node_struct* firstCar;
    struct TCB_queue_node_struct* nextCar;
};

typedef struct TCB_queue_node_struct TCB_queue_node;
typedef struct TCB_queue_struct TCB_queue;

//This method is going to create a queue of threads
TCB_queue* TCB_queue_create();

//This method is going to check if queue is empty
int TCB_queue_is_empty(TCB_queue* tcb_list);

//This method is going to add a thread to the queue
int EnqueueTCB(TCB_queue* tcb_queue, TCB* tcb);

//This method is going to remove a thread from the queue
TCB* DequeueTCB(TCB_queue* tcb_queue);

//This method is going to check if an specific thread is in the queue
int TCB_queue_contains(TCB_queue* tcb_queue, TCB* tcb);

//This method get an specific thread from the queue
TCB* TCB_queue_get(TCB_queue* tcb_queue, int tid);


#endif	/* TCB_QUEUE_H */

