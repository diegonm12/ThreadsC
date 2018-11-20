
#ifndef DISPATCHER_H
#define	DISPATCHER_H
#include "TCB.h"

/*
This method is going to make a change of context
*/
void Dispatch(TCB* thread);

/*
This method is going to save the thread context of the thread that receives as a parameter
*/
int Save(TCB* thread);


#endif	/* DISPATCHER_H */

