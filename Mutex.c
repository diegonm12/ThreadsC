#include "Mutex.h"

//This method is going to initialize the mutext
mutext* mutext_create() {

    mutext* t = (mutext*) malloc(sizeof (mutext));   
    if (t == NULL) {      
        return NULL;
    } else {
        t->blocked = 0;
        t->idMutext = mutext_counter;
        t->threadsWaiting = TCB_list_create();         
        mutext_counter++;
        return t;
    }
}
