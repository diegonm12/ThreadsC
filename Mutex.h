#ifndef MUTEX_H
#define	MUTEX_H
#include <stdlib.h>
#include "TCB_list.h"

struct Mutext_struct {
    int idMutext;
    int blocked;
    struct TCB_list_struct* threadsWaiting;
};

typedef struct Mutext_struct mutext;
int mutext_counter;

//This method is going to initialize the mutext
mutext* mutext_create();

#endif	/* MUTEX_H */

