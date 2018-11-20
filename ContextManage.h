#ifndef CONTEXTMANAGE_H
#define	CONTEXTMANAGE_H
#include "ucontext.h"


/*
This method is going to create a new context
each time a thread is created a new context is created
*/
ucontext_t* make_context(void *(*function)(void *), void* arg, ucontext_t* link);


#endif	/* CONTEXTMANAGE_H */
