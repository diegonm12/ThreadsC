#ifndef BRIDGE_H
#define	BRIDGE_H
#include <stdlib.h>
#include "TCB.h"
#include "Car_Queue.h"
#include "Car_List.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct BridgeSideStruct  {
    Car_Queue* queueCarsSide; // the queue for the cars
    int lengthBridgeSide;   // the lenght of the bridge
    int semaphoreGreenSide; //time in green
    int KCars;  // amount of cars
    int percentAmbulanceSide;   // how many ambulances
    int percentRadioActiveSide; // how many radioactive cars
};

typedef struct BridgeSideStruct BridgeSide;

BridgeSide* buildBridgeSide(int lengthBridgeSide, int SpeedOfCar, int semaphoreGreenSide, int KCars,int percentAmbulanceSide,int percentRadioActiveSide,Car_Queue* queue);


typedef enum {
    OFFICER,
    SEMAPHORE,
    JUNGLE
} BrigdeController;

typedef enum {
    LEFT,
    RIGHT,
    NODIRECTION
} Direction;

struct BridgeStruct {
    struct BridgeSideStruct* leftSide;  // the bridges are going to handle the structure left and right 
    struct BridgeSideStruct* rightSide;
    struct Car_list* carsOnBridge;  // handles the cars in the bridge in any time
    BrigdeController controller;    // control in the bridge
    Direction direction;    //movements of the cars
    int gettingIntoTheBridge; // cars getting into the bridge
    int carsWaiting;    // cars waiting
   
};

typedef struct BridgeStruct Bridge;
Bridge* buildBridge( BridgeSide* leftSide, BridgeSide* rightSide,BrigdeController controller);
#endif	/* BRIDGE_H */

