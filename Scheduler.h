
#ifndef ROUNDROBIN_H
#define	ROUNDROBIN_H
#include "Thread.h"
#include "TCB.h"
#include <signal.h>
#include <sys/time.h>
#include "Dispatcher.h"
#include "TCB_Queue.h"

#define DeadLine 900 

//Data
int main_tid; // tid of  the main thread
TCB* threadCurrent; //Represents the actual thread
int count_TID; //Represents the thread id
int thread_counter; // Counts how many threads exist at a given time

TCB_list* all_threads; // List containing all threads that haven't ended
TCB_queue* RoundRobinQueue; //Round Robin Queue List
TCB_list* RaffleList; // List containing all threads that haven't ended
TCB_list* RealTimeList; //List containing all real time threads

int initScheduler(); //This method is going to initialize all of the structs need it for the scheduler
int create(ucontext_t* newcontext, Scheduler scht, int,int); //this method is going to create the thread
int ready(TCB* thread); //this method returns the id of the thread
int startQuantum(int ms); //this method initialize the quantum
void stopQuantum(); //this method is going to stop the quantum
void pause_timer(); //this method is going to pause the timer
void threadKill(TCB* thread); //this method kill threads
TCB* running(); //indicates which thread is running

TCB* getNextRoundRobin(); //get the next thread of the round robin queue
TCB* getNextRaffle(); //get the thread that wins the lottery

int verifyRealTime(); 
int sleepThread(TCB*, int); //this method sleep the thread
TCB* findTCB(int tid); //find a thread by the TID
int joinThreadtoThread(TCB* thread, TCB* waited_for); //this method calls TCB_BLOCK
void unblock_waiting_for_me(TCB* thread); //calls the unblock function 
void unblock(TCB* thread, TCB* waited_for); //unblock the thread specified by TID
int joinThread(TCB* thread, int waitID); //calls TCB_BLOCK
int ditachThread(int); //calls the function unblock_waiting_for_me

int getMaxTickets(); //get the amount of tickets
TCB* getWinner(int ticket); //received the winner ticket and find who win the loterry

TCB* getNexttoDeadLineRoundRobin(); 
TCB* getNexttoDeadLineRaffle();
TCB* getNextRealTime();

#endif	/* ROUNDROBIN_H */

