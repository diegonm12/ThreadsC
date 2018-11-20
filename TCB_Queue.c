#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TCB_Queue.h"

//This method is going to create a queue of threads
TCB_queue* TCB_queue_create() {
    TCB_queue* new_queue = (TCB_queue*) malloc(sizeof (TCB_queue));

    if (new_queue == NULL) {
        return NULL;
    } else {
        new_queue->firstCar = NULL;
        new_queue->nextCar = NULL;
        new_queue->count = 0;
        return new_queue;
    }
}

//This method is going to check if queue is empty
int TCB_queue_is_empty(TCB_queue* q) {
    return (q->firstCar == NULL && q->nextCar == NULL);
}

//This method is going to add a thread to the queue
int EnqueueTCB(TCB_queue *q, TCB *t) {
    TCB_queue_node* new_element = (TCB_queue_node*) malloc(sizeof (TCB_queue_node));

    if (new_element == NULL) {
        return ERROR;
    } else {
        new_element->data = t;
        new_element->next = NULL;

        if (TCB_queue_is_empty(q)) {
            q->firstCar = new_element;
            q->nextCar = new_element;
            q->count++;
        } else {
            (q->nextCar)->next = (TCB_queue_node*) malloc(sizeof (TCB_queue_node));
            (q->nextCar)->next = new_element;
            q->nextCar = (q->nextCar)->next;
            q->count++;
        }

        return NO_ERROR;
    }
}

//This method is going to remove a thread from the queue
TCB* DequeueTCB(TCB_queue* tcb_queue) {
    if (TCB_queue_is_empty(tcb_queue)) {
        return NULL;
    } else if ((tcb_queue->firstCar) == (tcb_queue->nextCar)) // queue has only one element
    {
        TCB_queue_node* element = tcb_queue->firstCar;

        tcb_queue->firstCar = NULL;
        tcb_queue->nextCar = NULL;
        tcb_queue->count--;
        return element->data;
    } else {
        TCB_queue_node* element = tcb_queue->firstCar;

        tcb_queue->firstCar = (tcb_queue->firstCar)->next;
        tcb_queue->count--;
        return element->data;
    }
}

//This method get an specific thread from the queue
TCB* TCB_queue_get(TCB_queue* tcb_queue, int tid) {

    TCB_queue_node* pointer = tcb_queue->firstCar;
    while (pointer != NULL) {
        if ((pointer->data)->thread_id == tid) {
            return (pointer->data);
        }
        pointer = pointer->next;
    }
    return NULL;
}
