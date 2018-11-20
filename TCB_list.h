#ifndef TCB_LIST_H
#define	TCB_LIST_H
#include "TCB.h"

#define NO_ERROR 0
#define ERROR -1

typedef struct TCB_struct TCB;

struct TCB_list_node_struct {
    struct TCB_struct* data;
    struct TCB_list_node_struct* previous;
    struct TCB_list_node_struct* next;
};

struct TCB_list_struct {
    int count;
    struct TCB_list_node_struct* firstCar;
    struct TCB_list_node_struct* nextCar;
};

typedef struct TCB_list_node_struct TCB_list_node;
typedef struct TCB_list_struct TCB_list;

//This method is goint to create a list of threads
TCB_list* TCB_list_create();

//This method is going to check if the list is empty
int TCB_list_is_empty(TCB_list* tcb_list);

//This method is going to add a thread on the list
int TCB_list_add(TCB_list* tcb_list, TCB* tcb);

//This method is going to remove a thread from the list
TCB* TCB_list_remove(TCB_list* tcb_list, TCB* tcb);

//This method is goint to get a thread from the list
TCB* TCB_list_get(TCB_list* tcb_list, int tid);

#endif	/* TCB_LIST_H */

