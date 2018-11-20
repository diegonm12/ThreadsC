#ifndef THREAD_H
#define	THREAD_H

#include "ucontext.h"
#include <stdio.h>
#include "stdlib.h"
#include "ContextManage.h"
#include "Scheduler.h"
#include "Dispatcher.h"
#include "signal.h"
#include "Mutex.h"

//Data
ucontext_t* KillContext;

typedef enum {
    raffler,
    roundrobin,
    realtime,
} TypeSchedule;

TypeSchedule scht;

//This method creates a new thread
int mythread_create(void *(*function)(void *), Scheduler scht, int tickets, void *arg,int);

//This method initializes all the structs at the beginning
int mythread_init();

/*This method suspends execution of the calling thread until the target thread terminates, 
unless the target thread has already terminated */
void mythread_join(int waitTID);

//This method kills the thread
int mythread_end();

//This method is sleep the thread for an amount of time
void mythread_sleep(int);

//This method detach a thread
int mythread_detach(int tid);

//This method gets the thread TID
int mythread_id();

//This method set the scheduler to the thread
void mythread_setsched();

//This method yield the processor
void mythread_yield();

//Initialize the mutext
mutext* mymutex_init();

//This method get the lock
int mymutex_lock(mutext* mt);

//This method release the lock
int mymutex_unlock(mutext* mt);

//This method checks if there is a lock
int mymutex_trylock(mutext* mt);

//This method destroy the mutex
int mymutex_destroy(mutext* mt);


static int RealTimeScheduler(); 
static void checkForBlockThreads();
static void *idle(void *x);
static void changeCurrentThread();
static int joinCurrentThread(int);
static int threadCurrentMutextLock(mutext* mt);
static void sleepCurrentThread(int sec);
static void *killThread(void *x);
static void initKillContext();
static void signal_scheduler();
static int verifyTime(time_t start, int waitTime);


int ScheduleRoundRobin();
int ScheduleRaffle();
int ScheduleRealTime();


#endif	/* THREAD_H */
