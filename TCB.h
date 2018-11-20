#ifndef TCB_H
#define	TCB_H
#include "ucontext.h"
#include "time.h"
#include "TCB_list.h"

#define NO_ERROR 0
#define ERROR -1

typedef enum {
    READY,
    RUNNING,
    BLOCKED
} State;

typedef enum {
    RAFFLE,
    ROUNDROBIN,
    REALTIME,
    DEFAULT,
} Scheduler;

struct TCB_struct {
    int thread_id;
    ucontext_t* context;
    State state;
    int waitTime;
    clock_t start;
    struct TCB_list_struct* joinThreads;
    int waitJoin;
    int detach;
    Scheduler scht;
    int tickets;
    int quantum;
    int timelife;
    time_t genesis;
    int firstTime;
};

typedef struct TCB_struct TCB;

//This method creates the thread
TCB* TCB_create(int thread_id, ucontext_t* context, Scheduler scht, State state, int,int);

//This method check if two threads are equal
int TCB_equals(TCB* t1, TCB* t2);

//This method blocks a thread
int TCB_block(TCB* waiting_thread, TCB* blocking_thread);

//This method removes a thread from the join queue of threads
int TCB_unblock(TCB* waiting_thread, TCB* blocking_thread);

//This method check if a thread is blocked
int TCB_is_blocked(TCB* thread);

char* State_to_string(State state);



#endif	/* TCB_H */

