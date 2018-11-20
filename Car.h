#ifndef CAR_H
#define	CAR_H
#include <stdlib.h>
typedef enum {
    AMBULANCE,
    RADIOACTIVE,
    NORMAL
} TypeCar;
typedef enum {
    LEFTQUEUE,
    RIGHTQUEUE
} QueueOfSides;
struct CarStruct { // the struct of a car with all the parameters a car needs
    int SpeedOfCar;
    TypeCar type;
    int bridgePos;
    int askContinue;
    int bridgeID;
    int carID;
    int continueOnRoad;
    QueueOfSides queueSide;
};
typedef struct CarStruct Car;
Car* createCar(TypeCar type, int SpeedOfCar, int bridgeID, QueueOfSides queueSide, int bridgePos); // initialize the parameters above, create a car
void* moveCarThread(void *mCar); // move the cars
#endif	/* CAR_H */
