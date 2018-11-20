#include "TCB.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//This method creates the thread
TCB* TCB_create(int tid, ucontext_t* context, Scheduler scht, State state, int tickets,int timelife) {
    TCB* t = (TCB*) malloc(sizeof (TCB));
    if (t == NULL) {
        return NULL;
    } else {
        t->thread_id = tid;
        t->context = context;
        t->state = state;
        t->start = 0;
        t->waitTime = 0;
        t->waitJoin = 0;
        t->joinThreads = TCB_list_create();
        t->detach = 0;
        t->scht = scht;
        t->tickets = tickets;
        t->quantum = 5000;
        t->genesis = clock();
        t->timelife = timelife;
        t->firstTime = 1;
        return t;
    }
}


//This method check if two threads are equal
int TCB_equals(TCB* t1, TCB* t2) {
    return (t1->thread_id == t2->thread_id);
}

//This method check if a thread is blocked
int TCB_is_blocked(TCB* thread) {
    return thread->state == BLOCKED;
}

char* State_to_string(State state) {
    char* state_string;
    switch (state) {
        case READY:
            state_string = "ready";
            break;
        case RUNNING:
            state_string = "running";
            break;
        case BLOCKED:
            state_string = "blocked";
            break;
    }

    return state_string;
}

//This method blocks a thread
int TCB_block(TCB* newJoinThread, TCB* blocking_thread) {

    if (blocking_thread == NULL) {
        return ERROR;
    } else if (newJoinThread == NULL) {
        return ERROR;
    } else {
        TCB_list_add(blocking_thread->joinThreads, newJoinThread);
        return NO_ERROR;
    }
}

//This method removes a thread from the join queue of threads
int TCB_unblock(TCB* waiting_thread, TCB* blocking_thread) {

    if (blocking_thread == NULL) {
        return ERROR;
    } else if (waiting_thread == NULL) {
        return ERROR;
    } else {
        TCB_list_remove(blocking_thread->joinThreads, waiting_thread);
        waiting_thread->state = READY;
        waiting_thread->waitJoin = 0;
        return NO_ERROR;
    }
}

