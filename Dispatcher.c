#include "Dispatcher.h"

/*
This method is going to make a change of context
*/
void Dispatch(TCB* thread) {
    setcontext(thread->context);
}

/*
This method is going to save the thread context of the thread that receives as a parameter
*/
int Save(TCB* thread) {
    int success = getcontext(thread->context);
    return success;
}
