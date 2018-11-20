#include "TCB_list.h"
#include <stdlib.h>
#include <stdio.h>

//This method is goint to create a list of threads
TCB_list* TCB_list_create() {
    
    TCB_list* new_list = (TCB_list*) malloc(sizeof (TCB_list));
    if (new_list == NULL) {
        return NULL;
    } else {
        new_list->firstCar = NULL;
        new_list->nextCar = NULL;
        new_list->count = 0;
        return new_list;
    }
}

//This method is going to check if the list is empty
int TCB_list_is_empty(TCB_list* tcb_list) {
    return (tcb_list->firstCar == NULL && tcb_list->nextCar == NULL);
}

//This method is going to add a thread on the list
int TCB_list_add(TCB_list* tcb_list, TCB* tcb) {
    //("Added to list %d \n", tcb->thread_id);
    TCB_list_node* new_node = (TCB_list_node*) malloc(sizeof (TCB_list_node));

    if (new_node == NULL) {
        return ERROR;
    } else if (tcb_list->nextCar == NULL) // list is empty
    {
        new_node->data = tcb;

        tcb_list->nextCar = new_node;
        tcb_list->nextCar->next = NULL;
        tcb_list->nextCar->previous = NULL;

        tcb_list->firstCar = new_node;
        tcb_list->firstCar->next = NULL;
        tcb_list->firstCar->previous = NULL;

        tcb_list->count++;

        return NO_ERROR;
    } else if ((tcb_list->firstCar)->next == NULL) // list has only one element
    {
        new_node->data = tcb;

        (tcb_list->firstCar)->next = new_node;
        (tcb_list->nextCar)->next = new_node;
        new_node->previous = tcb_list->nextCar;
        new_node->next = NULL;

        tcb_list->nextCar = (tcb_list->nextCar)->next;

        tcb_list->count++;

        return NO_ERROR;
    } else {
        new_node->data = tcb;

        (tcb_list->nextCar)->next = new_node;
        new_node->previous = tcb_list->nextCar;
        new_node->next = NULL;

        tcb_list->nextCar = (tcb_list->nextCar)->next;

        tcb_list->count++;

        return NO_ERROR;
    }
}

//This method is going to remove a thread from the list
TCB* TCB_list_remove(TCB_list* tcb_list, TCB* tcb) {
    //printf("Remove from list %d \n", tcb->thread_id);
   
    TCB_list_node* pointer = tcb_list->firstCar;

    while (pointer != NULL) {
        if (TCB_equals(pointer->data, tcb)) {
            TCB_list_node* to_be_removed = pointer;

            if ((tcb_list->firstCar)->next == NULL) // list has only one element
            {
                tcb_list->firstCar = NULL;
                tcb_list->nextCar = NULL;
                tcb_list->count--;
            } else if (pointer->previous == NULL) // list has more than one element and first element is to be removed
            {
                tcb_list->firstCar = (tcb_list->firstCar)->next;
                (tcb_list->firstCar)->previous = NULL;
                tcb_list->count--;
            } else if (pointer->next == NULL) // list has more than one element and last element is to be removed
            {
                (pointer->previous)->next = pointer->next;
                tcb_list->nextCar = pointer->previous;
                tcb_list->count--;
            } else // default
            {
                (pointer->previous)->next = pointer->next;
                pointer->next->previous = pointer->previous;
                tcb_list->count--;
            }

            TCB* data = to_be_removed->data;

            free(to_be_removed);

            return data;
        }

        pointer = pointer->next;
    }

    return NULL;
}

//This method is goint to get a thread from the list
TCB* TCB_list_get(TCB_list* tcb_list, int tid) {

    TCB_list_node* pointer = tcb_list->firstCar;
    while (pointer != NULL) {
        if ((pointer->data)->thread_id == tid) {
            return (pointer->data);
        }
        pointer = pointer->next;
    }

    return NULL;
}