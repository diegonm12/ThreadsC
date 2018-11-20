#ifndef CAR_LIST_H
#define	CAR_LIST_H
#include "Car.h"

#define NO_ERROR 0
#define ERROR -1

typedef struct CarStruct Car;

struct listCarStruct {
    struct CarStruct* data;
    struct listCarStruct* previous;
    struct listCarStruct* next;
};

struct carLStruct {
    int count;
    struct listCarStruct* firstCar;
    struct listCarStruct* nextCar;
};

typedef struct listCarStruct carNode;
typedef struct carLStruct Car_list;

//This method is going to create and initialize the list of cars
Car_list* Car_list_create();

//This method is going to check if the list of cars is empty
int Car_list_is_empty(Car_list* Car_list);

//This method is going to add cars on the list
int Car_list_add(Car_list* Car_list, Car* Car);

//This method is going to remove a car from the list
Car* Car_list_remove(Car_list* Car_list, int bridgePos);

//This method is going to get a car from the list
Car* Car_list_get(Car_list* Car_list, int pos);

//This method is goint to print the list of cars
void printList(Car_list* carList,int bridgeID);

//This method is going verify if there is a radioactive car on the list
int verifyRadioActiveonList(Car_list* Car_list,QueueOfSides queueSide);

//This method is going to move the cars across the bridge
void moveCarsOnBridge(Car_list* carList);




#endif	/* CAR_LIST_H */

