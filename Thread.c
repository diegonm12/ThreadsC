#include "Thread.h"

int ticket;

//This method initializes all the structs at the beginning
int mythread_init() {
    
    ticket=0;

    ucontext_t* main_context = (ucontext_t*) malloc(sizeof (ucontext_t)); //calls for the main context memory
    int gotContext = 0;
    if (main_context == NULL) {  
        return ERROR;
    }
    int code = initScheduler(); // initializes the lists, queue and make a master Round Robin and thread tid = 0
    if (code < 0) {
        return ERROR;
    }
  //  printf("Contex ANTES del cambio: %d\n", getcontext(main_context));
    
    initKillContext(); //create a new context

  //  printf("Contex DESPUES del cambio: %d\n", getcontext(main_context));
  
    int result = getcontext(main_context); 

    if (!gotContext) {
        gotContext = 1;
        if (result == -1) {
            return ERROR;
        }
        main_tid = create(main_context, ROUNDROBIN, 1, 999999999); 
        if (main_tid < 0) {
            return ERROR;
        }
        // Sets main thread to run;
        scht = roundrobin;
        RealTimeScheduler(); 
    }

    //Init signal handler
    struct sigaction act, oact;
    act.sa_handler = signal_scheduler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGPROF, &act, &oact);

    //IDLEContext
    mythread_create(idle, ROUNDROBIN, 0, 0, 999999999);


    return NO_ERROR;

}

//This method creates a new thread
int mythread_create(void *(*function)(void *), Scheduler scht, int tickets, void *arg, int timelife) {

    ucontext_t* NewThread = make_context(function, arg, KillContext);
    if (NewThread == NULL) {
        return ERROR;
    }
    if(scht==DEFAULT){
        scht=ROUNDROBIN;
    }
    int code = create(NewThread, scht, tickets, timelife); // Creates thread and inserts it on queue

    //int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
    
    if (code < 0) {
        return ERROR;
    } else {
        return code; // Contains thread id
    }
}

//This method is sleep the thread for an amount of time
void mythread_sleep(int sec) {

    stopQuantum();
    int gotSleep = 0;
    Save(running()); //save the actual context
    if (!gotSleep) {
        gotSleep = 1;
        sleepCurrentThread(sec);
    } else {
        return;
    }
}

/**
 * Ends the execution of a thread
 * @return 
 */
int mythread_end() {
    stopQuantum();
    TCB* thread = running();
    threadKill(thread);
    return RealTimeScheduler();
}

/*
 * Make a thread  wait until the thread with the id waitID ends.
 */
void mythread_join(int waitTID) {
    stopQuantum();
    int gotJoin = 0;
    Save(running()); // save the actual context
    if (!gotJoin) {
        gotJoin = 1;
        joinCurrentThread(waitTID);
    } 
}

//This method yield the processor
void mythread_yield() {
    stopQuantum();
    int gotYield = 0;
    Save(running());
    if (!gotYield) {
        gotYield = 1;
        changeCurrentThread();
    } else {
        return;
    }
}

//This method detach a thread
int mythread_detach(int tid) {
    return ditachThread(tid);
}

//This method gets the thread TID
int mythread_id() {
    return running()->thread_id;
}

//This method set the scheduler to the thread
void mythread_setsched() {
    if (running()->scht == ROUNDROBIN) {
        running()->scht = RAFFLE;
    } else if (running()->scht == RAFFLE) {
        running()->scht = ROUNDROBIN;
    }
}

////////////////////////////////////////////////////////////////////////////////

/**
 * This function is call once a quantum ends.
 */
void signal_scheduler() {

    int gotContext = 0;
    Save(running());
    if (!gotContext) {
        gotContext = 1;
        changeCurrentThread();
    } else {
        return;
    }
}

/**
 * Saves the actual context and call the scheduler
 */
void changeCurrentThread() {
    ready(running()); // enqueues the actual thread
    RealTimeScheduler(); // ask for a new thread
}

/**
 * Makes a 50/50 decision about who is the next scheduler that must run.
 * @return 
 */
int RealTimeScheduler() {// 50-50 

    checkForBlockThreads();
    
    
    if(!verifyRealTime())
    {
        //printf("Real time %d\n",ticket);
        ticket++;
        if(ticket>=10)
        {      
            ticket=0;
            if (scht == roundrobin)
            {            
                scht = raffler;
                return ScheduleRoundRobin();  //scheduling like round robin
            } 
            else if (scht == raffler)
            {                
                scht = roundrobin;
                return ScheduleRaffle(); //scheduling like lottery
            }

        }
        
        return ScheduleRealTime();
    }
    else{
        ticket=0;
        //printf("Hice un cambio %d\n",ticket);
        if (scht == roundrobin) {
            //printf("Round Robin\n");
            scht = raffler;
            return ScheduleRoundRobin();  //scheduling like round robin

        } else if (scht == raffler) {
            //printf("raffler\n");
            scht = roundrobin;
            return ScheduleRaffle(); //scheduling like lottery
        }
    }

}

/**
 * Exexutes a RoundRobin scheduler
 * @return 
 */
int ScheduleRoundRobin() { //scheduler round robin real time

    
    TCB* thread;
    
    thread = getNextRoundRobin(); //if theres no real time, get the firstCar of the queue
    

    threadCurrent = thread;
    if (thread != NULL) { 
        if (thread->state == READY) {
            thread->state = RUNNING;
            if (thread->firstTime == 1) {
                thread->firstTime = 0;
                thread->genesis = clock();
            }
            startQuantum(thread->quantum); 
            Dispatch(thread); 
            return ERROR; // If execution reached this point, an error ocurred
        }
    } else {

        //printf("Busque un round robin, pero era lottery\n");

        if (thread_counter > 0) {
            return RealTimeScheduler();
        } else {// Ready queue emptied. All threads are now finished.}
            return NO_ERROR;
        }
    }
}

/**
 * Exexutes a Raffle scheduler
 * @return 
 */
int ScheduleRaffle() {

    TCB* thread; 
     
    thread = getNextRaffle(); 
  
    threadCurrent = thread;

    if (thread != NULL) {      
        if (thread->state == READY) {
            thread->state = RUNNING;
            if (thread->firstTime == 1) {
                thread->firstTime = 0;
                thread->genesis = clock();
            }
            startQuantum(thread->quantum);
            Dispatch(thread);
            return ERROR; // If execution reached this point, an error ocurred
        }
    } else {        
        if (thread_counter > 0) {
            return RealTimeScheduler();
        } else {// Ready queue emptied. All threads are now finished.}
            return NO_ERROR;
        }
    }
}

int ScheduleRealTime() { 
    
    TCB* thread;
    TCB* dead = getNextRealTime(); 
    if (dead != NULL) {
        thread = dead;
        TCB_list_remove(RealTimeList, thread); 
    }

    threadCurrent = thread;

    if (thread != NULL) {
       // printf("--------------------------------------------------------\n");
        if (thread->state == READY) {
            thread->state = RUNNING;
            if (thread->firstTime == 1) {
                thread->firstTime = 0;
                thread->genesis = clock();
            }
            startQuantum(thread->quantum);
            Dispatch(thread);
            return ERROR; 
        }

    } else {        
        if (thread_counter > 0) {
            return RealTimeScheduler();
        } else {
            return NO_ERROR;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////

void initKillContext() { 
    KillContext = make_context(killThread, 0, 0);
}

void *killThread(void *x) {

    TCB* thread = running();
    threadKill(thread);
    RealTimeScheduler();

}

// Check if a thread has already served his time blocked ready to pass
void checkForBlockThreads() {

    TCB_list_node* pointer = all_threads->firstCar;
    while (pointer != NULL) {
        if ((pointer->data)->state == BLOCKED) {
            if ((pointer->data)->waitJoin == 0) {
                int result = verifyTime((pointer->data)->start, (pointer->data)->waitTime);
                if (result == 1) {
                    //printf("Aqui es donde llamo el ready\n");
                    ready(pointer->data);
                }
            }
        }
        pointer = pointer->next;
    }
}

void sleepCurrentThread(int sec) {
    sleepThread(running(), sec); 
    RealTimeScheduler(); 
}

int joinCurrentThread(int waitID) {

    int result = joinThread(running(), waitID);
    if (result != ERROR) {
        return RealTimeScheduler();  
    } else {
        return ERROR;
    }
}

int verifyTime(time_t start, int waitTime) {

    clock_t end = clock();
    double dif = (end - start) / (double) 1000;
    if (dif >= waitTime) {
        return 1;
    } else {
        return 0;
    }
}

void *idle(void *x) {
    while (1);
}

mutext* mymutex_init() {
    mutext* t = mutext_create();
    return t;
}

int mymutex_lock(mutext* mt) {

    if (mt->blocked == 1) { 
        int gotJoin = 0;
        Save(running()); 
        if (!gotJoin) {
            gotJoin = 1;
            return threadCurrentMutextLock(mt);
        } else {
            return 0;
        }

    } else {
        mt->blocked = 1; 
        return 1;
    }
}

int mymutex_unlock(mutext* mt) {
    if (mt->threadsWaiting->count > 0) {
        TCB_list_node* pointer = mt->threadsWaiting->firstCar;
        (pointer->data)->waitJoin = 0;
        ready(pointer->data);
        TCB_list_remove(mt->threadsWaiting, pointer->data);
    }
    mt->blocked = 0; 
    return 1; 
}

int mymutex_trylock(mutext* mt) {
    if (mt->blocked == 1) { 
        return 0;
    } else {
        return 1;
    }
}

int mymutex_destroy(mutext* mt) {

    if (mt->idMutext != -1) {
        TCB_list_node* pointer = mt->threadsWaiting->firstCar;
        while (pointer != NULL) {
            (pointer->data)->waitJoin = 0;
            ready(pointer->data);
            pointer = pointer->next;
        }
        mt->idMutext = -1;
        mt->blocked = 'x';
        free(mt->threadsWaiting);
        free(mt);
        return NO_ERROR;

    } else {
        return ERROR;
    }
}

int threadCurrentMutextLock(mutext* mt) {
    stopQuantum();
    running()->state = BLOCKED;
    running()->waitJoin = 1;
    TCB_list_add(mt->threadsWaiting, running());
    return RealTimeScheduler(); 
}