
#ifndef Car_Queue_H
#define	Car_Queue_H

#define NO_ERROR 0
#define ERROR -1
#include "Car.h"
#include "Thread.h"

struct Car_Queue_node_struct {
    struct CarStruct* data;
    struct Car_Queue_node_struct* next;
};

struct Car_Queue_struct {
    int count;
    int radioActiveCount;
    struct Car_Queue_node_struct* first;
    struct Car_Queue_node_struct* next;
};

typedef struct Car_Queue_node_struct Car_Queue_node;
typedef struct Car_Queue_struct Car_Queue;


//This method is going to create and initialize the queue
Car_Queue* createQueue();

//This method is going to check if the queue is empty
int Car_Queue_is_empty(Car_Queue* car_list);

//This method is going to add a car to the queue
int EnqueueCar(Car_Queue* Car_Queue, Car* car);

//This method is going to extract a car from the queue
Car* DequeueCar(Car_Queue* Car_Queue);

//This method is going to check if the queue have an specific car
int Car_Queue_contains(Car_Queue* Car_Queue, Car* car);

//This method is going to get a car from the queue
Car* Car_Queue_get(Car_Queue* Car_Queue, int carID);

//This method is going to print the queue
void printQueue(Car_Queue* Car_Queue,int queueID);

//This method is going to fill the queue of the jungle law
Car_Queue* creatingQueueOfCarsJungle(Car_Queue* Queue,float PercentOfAmbulance, float PercentOfRadioactive, int speedNormalCar, int speedAmbulance,
 int speedRadioactive,int carsQuantity, int bridgeID, QueueOfSides queueSide, int bridgePos);

//This method is going to remove the cars of the queue of the jungle law
Car* carJungleRemove(Car_Queue* car_Queue, int carID);

void getFileName(char* file,int IDFile);


#endif	/* Car_Queue_H */

