#include "Scheduler.h"

//This method is going to initialize all of the structs need it for the scheduler
int initScheduler() {

    RoundRobinQueue = TCB_queue_create(); //Round Robin

    RaffleList = TCB_list_create(); //Lottery
    RealTimeList = TCB_list_create(); //RealTime
   
    all_threads = TCB_list_create();

    ucontext_t current;
    threadCurrent = TCB_create(0, &current, ROUNDROBIN, READY, 0, 0); 

    if (RoundRobinQueue == NULL || all_threads == NULL || RaffleList == NULL|| RealTimeList == NULL) { 
        return ERROR;
    } else {
        count_TID = 0;
        thread_counter = 0;
        return NO_ERROR;
    }
}

//get the next thread of the round robin queue
TCB* getNextRoundRobin() { 
    TCB* thread = DequeueTCB(RoundRobinQueue);
    if (thread == NULL) {
        return NULL;
    } else {
        return thread;
    }
}

//get the thread that wins the lottery
TCB* getNextRaffle() {     
    TCB* thread;
   
    int empty = TCB_list_is_empty(RaffleList); 

    if (!empty) {      
       
        int max = getMaxTickets();
        int winner = (rand() % max);
        thread = getWinner(winner);
      
        TCB_list_remove(RaffleList, thread);

        return thread;
    } else {
        return NULL;
    }
}


TCB* getNextRealTime() {

    TCB_list_node* pointer = RealTimeList->firstCar;
    TCB* nextToDead = NULL;

    int remaining_last = 99999999;
    double hasBeenLifeLast = 0;

    while (pointer != NULL) {

        int timelife = (pointer->data)->timelife;
        double hasBeenLife = (clock() - (pointer->data)->genesis) / (double) 1000;
        int remaining = timelife - hasBeenLife;
        if (remaining < remaining_last && remaining < DeadLine) {
            nextToDead = pointer->data;
            remaining_last = remaining;
            hasBeenLifeLast = hasBeenLife;
        }
        pointer = pointer->next;
    }

    if (nextToDead != NULL) {
        return nextToDead;       
    }
    return NULL;
}

int verifyRealTime() {

    return TCB_list_is_empty(RealTimeList);
}

//get the amount of tickets
int getMaxTickets() { 
    int max = 0;
    TCB_list_node* pointer = RaffleList->firstCar;
    while (pointer != NULL) {
        max += (pointer->data)->tickets;
        pointer = pointer->next;
    }
    return max;
}

//received the winner ticket and find who win the loterry
TCB* getWinner(int ticket) {
    int ticket_count = 0; 
    TCB_list_node* pointer = RaffleList->firstCar;
    TCB* winner;
    while (pointer != NULL) {
        ticket_count += (pointer->data)->tickets;
        if (ticket <= ticket_count) {
            winner = pointer->data;
            break;
        }
        pointer = pointer->next;
    }
    return winner;
}

//remove a thread from the list of all threads
void threadKill(TCB* thread) { 
    unblock_waiting_for_me(thread);
    TCB_list_remove(all_threads, thread); // Removes thread from list of current threads
    thread_counter--;
    free(thread->joinThreads); // Frees list of threads blocked by the thread that exited
    free(thread); // Frees pointer to thread that exited
}

//calls the unblock function
void unblock_waiting_for_me(TCB* thread) {    

    TCB_list_node* pointer = (thread->joinThreads)->firstCar;
    while (pointer != NULL) {
        unblock(pointer->data, thread);
        pointer = pointer->next;
    }
}

//unblock the thread specified 
void unblock(TCB* thread, TCB* waited_for) {
    TCB_unblock(thread, waited_for);
    ready(thread);
}

//this method is going to create the thread
int create(ucontext_t* newcontext, Scheduler scht, int tickets, int timelife) { 
    
    TCB* thread = TCB_create(count_TID, newcontext, scht, READY, tickets, timelife);

  
    count_TID = count_TID + 1;
    thread_counter = thread_counter + 1;

    if (thread == NULL) {
        return ERROR;
    }

    int result = TCB_list_add(all_threads, thread); 
   
    if (result == ERROR) {
        return ERROR;
    }

    int tID = ready(thread);

    return tID;
}

//this method returns the id of the thread
int ready(TCB* thread) { 
   
    if (thread->scht == ROUNDROBIN) {//Round Robin
        int could_enqueue = EnqueueTCB(RoundRobinQueue, thread);
        if (could_enqueue == ERROR) {
            return ERROR;
        } else {
            thread->state = READY;
            return thread->thread_id;
        }
    } else if (thread->scht == RAFFLE) {//Lottery
     
        //printf("Volvi a ser ready\n");
     
        int could_list = TCB_list_add(RaffleList, thread);
        if (could_list == ERROR) {
            return ERROR;
        } else {
            thread->state = READY;
            return thread->thread_id;
        }    
    } else if (thread->scht == REALTIME) {//RealTime
     
        
        int could_list = TCB_list_add(RealTimeList, thread);
        if (could_list == ERROR) {
            return ERROR;
        } else {
            thread->state = READY;
            return thread->thread_id;
        }
    }
     else {
        printf("No se asigno scheduler\n");
    }

}

//adds a thread to the round robin queue, but adds the thread blocked
int block(TCB* thread) { 
    
    int could_enqueue = EnqueueTCB(RoundRobinQueue, thread);
    if (could_enqueue == ERROR) {
        return ERROR;
    } else {
        thread->state = BLOCKED;
        return thread->thread_id;
    }
}

//this method sleep the thread
int sleepThread(TCB* thread, int sec) { 
    
    TCB* threadInList = findTCB(thread->thread_id);
    threadInList->state = BLOCKED;
    threadInList->waitTime = sec;
    threadInList->start = clock();
    return threadInList->thread_id;
}

//receives the thread and the thread ID you have to wait, do join of the threads 
int joinThread(TCB* thread, int waitID) { 
 
    TCB* threadInList = findTCB(thread->thread_id);
    TCB* waited_thread = findTCB(waitID);

    if (waited_thread == NULL) {// thread is over
        return ERROR;
    }

    if (waited_thread->detach == 1) {//thread not allow to make join
        return ERROR;
    }

    TCB_block(threadInList, waited_thread); //blocks the thread with which it has to wait

    threadInList->state = BLOCKED;
    threadInList->waitJoin = 1;
    return threadInList->thread_id;

}

//returns the thread of the thread list, by the tid
TCB* findTCB(int tid) { 
    return TCB_list_get(all_threads, tid);
}

//join 2 threads, unlike the other method in this the two threads are passed directly.
int joinThreadtoThread(TCB* jointThread, TCB* waited_for) { 
    return TCB_block(jointThread, waited_for);
}

//Remove the joins of a thread
int ditachThread(int tid) { 
    TCB* waited_thread = findTCB(tid);
    if (waited_thread == NULL) {
        return ERROR;
    }
    waited_thread->detach = 1;
    unblock_waiting_for_me(waited_thread);
    return waited_thread->thread_id;
}

//Returns the thread that is running
TCB* running() { 
    return threadCurrent;
}

//this method initialize the quantum
int startQuantum(int ms) {
    struct itimerval timeslice;
    timeslice.it_value.tv_sec = 0;
    timeslice.it_value.tv_usec = ms;
    timeslice.it_interval.tv_sec = 0;
    timeslice.it_interval.tv_usec = 0;
    setitimer(ITIMER_PROF, &timeslice, NULL);
}

//this method is going to stop the quantum
void stopQuantum() {
    setitimer(ITIMER_PROF, NULL, NULL);
}
