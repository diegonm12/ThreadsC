//-----------------------------------------------------------------------MUTEX------------------------------------------------------------------------------------
#include "Thread.h"

int counter;
mutext* lock;


void* doSomeThing(void *arg)
{
    printf("Entre no hay mutex lock: %d\n",mymutex_trylock(lock));
    
    mymutex_lock(lock);

    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d started\n", counter);

    for(i=0; i<(0xFFFFFFFF);i++);

    printf("\n Job %d finished\n", counter);

    mymutex_unlock(lock);

    printf("Sali del mutex\n");

    return NULL;
}



int main() 
{
    mythread_init();
    int i = 0;
   
    lock = mymutex_init();
   
    if (lock == 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    int inc_x_thread;
    int inc_y_thread;
    inc_x_thread=mythread_create(doSomeThing, REALTIME, 0, & i, 34);
    inc_y_thread=mythread_create(doSomeThing, REALTIME, 0, & i, 34);   

    mythread_join(inc_x_thread);
    mythread_join(inc_y_thread);
    mymutex_destroy(lock);

    return 0;
}