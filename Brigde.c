#include "Bridge.h"
// The creation of the bridges is the responsability for this method
Bridge* buildBridge( BridgeSide* leftSide, BridgeSide* rightSide,BrigdeController controller)
{
    Bridge* bridgeInConstruction = (Bridge*) malloc(sizeof (Bridge)); // reserves the memory to store a bridge
    if(bridgeInConstruction == NULL){
        return NULL;
    }
    else
    {
        bridgeInConstruction->leftSide = leftSide;  // assigment of the left side parameter to the new bridge
        bridgeInConstruction->rightSide = rightSide; // assigment of the right side parameter to the new bridge
        bridgeInConstruction->controller = controller; // assigment of the controller  parameter to the new bridge
        bridgeInConstruction->direction = NODIRECTION; // assigment of the direction  parameter to the new bridge
        bridgeInConstruction->carsOnBridge = Car_list_create(); // assigment of a list to handle cars in the new bridge
        bridgeInConstruction->gettingIntoTheBridge = 0; // default number no cars in the construction of the bridge
        bridgeInConstruction->carsWaiting = 0;  // default value
        return bridgeInConstruction;
    }
}
//This method is going to create the structure that contains all of the data need it on one side of the bride 
BridgeSide* buildBridgeSide(int lengthBridgeSide, int SpeedOfCar, int semaphoreGreenSide, int KCars,int percentAmbulanceSide,int percentRadioActiveSide,
    Car_Queue* queue){
    BridgeSide* bridgeSideInConstruction = (BridgeSide*) malloc(sizeof (BridgeSide));
    if(bridgeSideInConstruction == NULL){
        return NULL;
    }
    else{
        bridgeSideInConstruction->queueCarsSide = queue;
        bridgeSideInConstruction->lengthBridgeSide = lengthBridgeSide;
        //bridgeSideInConstruction->SpeedOfCar = SpeedOfCar;
        bridgeSideInConstruction->semaphoreGreenSide = semaphoreGreenSide;
        bridgeSideInConstruction->KCars = KCars;
        bridgeSideInConstruction->percentAmbulanceSide = percentAmbulanceSide;
        bridgeSideInConstruction->percentRadioActiveSide = percentRadioActiveSide;
        return bridgeSideInConstruction;
    }
}