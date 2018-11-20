#include "Car_List.h"
#include <stdlib.h>
#include <stdio.h>


//This method is going to create and initialize the list of cars
Car_list* Car_list_create() {
    
    Car_list* new_list = (Car_list*) malloc(sizeof (Car_list));
    if (new_list == NULL) {
        return NULL;
    } else {
        new_list->firstCar = NULL;
        new_list->nextCar = NULL;
        new_list->count = 0;
        return new_list;
    }
}

//This method is going to check if the list of cars is empty
int Car_list_is_empty(Car_list* Car_list) {
    return (Car_list->firstCar == NULL && Car_list->nextCar == NULL);
}

//This method is going verify if there is a radioactive car on the list
int verifyRadioActiveonList(Car_list* Car_list,QueueOfSides queueSide)
{
    carNode* pointer = Car_list->firstCar;

    while (pointer != NULL) {
        if ((pointer->data)->type == RADIOACTIVE && (pointer->data)->queueSide==queueSide) {
            return 1;            
        }
        pointer = pointer->next;
    }

    return 0;

}

//This method is going to add cars on the list
int Car_list_add(Car_list* Car_list, Car* Car) {
    //("Added to list %d \n", Car->thread_id);
    carNode* new_node = (carNode*) malloc(sizeof (carNode));

    if (new_node == NULL) {
        return ERROR;
    } else if (Car_list->nextCar == NULL) // list is empty
    {
        new_node->data = Car;

        Car_list->nextCar = new_node;
        Car_list->nextCar->next = NULL;
        Car_list->nextCar->previous = NULL;

        Car_list->firstCar = new_node;
        Car_list->firstCar->next = NULL;
        Car_list->firstCar->previous = NULL;

        Car_list->count++;

        return NO_ERROR;
    } else if ((Car_list->firstCar)->next == NULL) // list has only one element
    {
        new_node->data = Car;

        (Car_list->firstCar)->next = new_node;
        (Car_list->nextCar)->next = new_node;
        new_node->previous = Car_list->nextCar;
        new_node->next = NULL;

        Car_list->nextCar = (Car_list->nextCar)->next;

        Car_list->count++;

        return NO_ERROR;
    } else {
        new_node->data = Car;

        (Car_list->nextCar)->next = new_node;
        new_node->previous = Car_list->nextCar;
        new_node->next = NULL;

        Car_list->nextCar = (Car_list->nextCar)->next;

        Car_list->count++;

        return NO_ERROR;
    }
}

//This method is going to remove a car from the list
Car* Car_list_remove(Car_list* Car_list, int bridgePos) {
    //printf("Remove from list %d \n", Car->thread_id);
   
   carNode* pointer = Car_list->firstCar;

    while (pointer != NULL) {
        if ((pointer->data)->bridgePos == 0) {
            carNode* to_be_removed = pointer;

            to_be_removed->data->bridgePos=bridgePos;
            to_be_removed->data->askContinue=0;

            if ((Car_list->firstCar)->next == NULL) // list has only one element
            {
                Car_list->firstCar = NULL;
                Car_list->nextCar = NULL;
                Car_list->count--;
            } else if (pointer->previous == NULL) // list has more than one element and first element is to be removed
            {
                Car_list->firstCar = (Car_list->firstCar)->next;
                (Car_list->firstCar)->previous = NULL;
                Car_list->count--;
            } else if (pointer->next == NULL) // list has more than one element and last element is to be removed
            {
                (pointer->previous)->next = pointer->next;
                Car_list->nextCar = pointer->previous;
                Car_list->count--;
            } else // default
            {
                (pointer->previous)->next = pointer->next;
                pointer->next->previous = pointer->previous;
                Car_list->count--;
            }
            free(to_be_removed);
        }

        pointer = pointer->next;
    }

    return NULL;
}

//This method is going to get a car from the list
Car* Car_list_get(Car_list* Car_list, int pos) {

    carNode* pointer = Car_list->firstCar;
    int i;
    for (i = 0; i < Car_list->count; ++i)
    {
       if(i == pos){
            return pointer;
       }
       pointer = pointer->next;
       i++;

    }

    return NULL;
}

//This method is going to move the cars across the bridge
void moveCarsOnBridge(Car_list* carList){

   carNode* pointer = carList->firstCar;

    while (pointer != NULL) {

        if((pointer->data)->askContinue == 1){
            if((pointer->data)->bridgePos<=0)
            {
                (pointer->data)->bridgePos=0;
            }
            else
            {
                (pointer->data)->bridgePos--;   
            }
        }        
        pointer = pointer->next;
    }
}


//This method is goint to print the list of cars
void printList(Car_list* carList,int bridgeID)
{
	char file [100];
	char command [100];
	if(bridgeID == 1){
		strcpy(file, "/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/COB1.txt");
		strcpy(command,"> ");
		strcat(command,file);
		system(command);
	}
	if(bridgeID == 2){
		strcpy(file, "/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/COB2.txt");
		strcpy(command,"> ");
		strcat(command,file);
		system(command);
	}
	if(bridgeID == 3){
		strcpy(file, "/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/COB3.txt");
		strcpy(command,"> ");
		strcat(command,file);
		system(command);
	}
	
	
    //printf("%s\n", "----------------Lista-----------------");
    if(carList == NULL){
        printf("%s\n", "No cars in the list");
    }
    else if(carList->count == 0){
        printf("%s\n", "No cars in the list");
    } 
    else{
         carNode* pointer = carList->firstCar;
         int i;

         for (i = 0; i < carList->count; ++i)
        {
            if(pointer->data->type==AMBULANCE)
            {
                if(pointer->data->queueSide==LEFTQUEUE)
                {
                     printf("Ambulance car: %d, Position on Bridge: %d, Queue: Left, Can car move: %d, IdCar: %d, Bridge: %d\n",
                      i,pointer->data->bridgePos,pointer->data->askContinue,pointer->data->carID,pointer->data->bridgeID);
					char completeCharArray [255];
					char writingCommand [255];
					char str[10];
					sprintf(str, "%d", pointer->data->bridgePos);
					strcpy(completeCharArray,str);
					strcat(completeCharArray,",");
					strcat(completeCharArray,"Ambulance");
					strcat(completeCharArray,",");
					strcat(completeCharArray,"left");
					strcat(completeCharArray,",");
					sprintf(str, "%d", pointer->data->carID);
					strcat(completeCharArray,str);
					strcat(completeCharArray,",");
					sprintf(str, "%d", pointer->data->bridgeID);
					strcat(completeCharArray,str);
					strcpy(writingCommand,"echo ");
					strcat(writingCommand,completeCharArray);
					strcat(writingCommand,">> ");
					strcat(writingCommand,file);
					system(writingCommand);
					
					
					
					
                }
                else
                {
                     printf("Ambulance car: %d, Position on Bridge: %d, Queue: Right, Can car move: %d, IdCar: %d, Bridge: %d\n", 
                        i,pointer->data->bridgePos,pointer->data->askContinue,pointer->data->carID,pointer->data->bridgeID);
					char completeCharArray [255];
					char writingCommand [255];
					char str[10];
					sprintf(str, "%d", pointer->data->bridgePos);
					strcpy(completeCharArray,str);
					strcat(completeCharArray,",");
					strcat(completeCharArray,"Ambulance");
					strcat(completeCharArray,",");
					strcat(completeCharArray,"right");
					strcat(completeCharArray,",");
					sprintf(str, "%d", pointer->data->carID);
					strcat(completeCharArray,str);
					strcat(completeCharArray,",");
					sprintf(str, "%d", pointer->data->bridgeID);
					strcat(completeCharArray,str);
					strcpy(writingCommand,"echo ");
					strcat(writingCommand,completeCharArray);
					strcat(writingCommand,">> ");
					strcat(writingCommand,file);
					system(writingCommand);

                }
               

            }
            else if(pointer->data->type==RADIOACTIVE)
            {
                if(pointer->data->queueSide==LEFTQUEUE)
                {
                     printf("Radioactive car: %d, Position on Bridge: %d, Queue: Left, Can car move: %d, IdCar: %d, Bridge: %d\n",
                      i,pointer->data->bridgePos,pointer->data->askContinue,pointer->data->carID,pointer->data->bridgeID);
					char completeCharArray [255];
					char writingCommand [255];
					char str[10];
					sprintf(str, "%d", pointer->data->bridgePos);
					strcpy(completeCharArray,str);
					strcat(completeCharArray,",");
					strcat(completeCharArray,"Radioactive");
					strcat(completeCharArray,",");
					strcat(completeCharArray,"left");
					strcat(completeCharArray,",");
					sprintf(str, "%d", pointer->data->carID);
					strcat(completeCharArray,str);
					strcat(completeCharArray,",");
					sprintf(str, "%d", pointer->data->bridgeID);
					strcat(completeCharArray,str);
					strcpy(writingCommand,"echo ");
					strcat(writingCommand,completeCharArray);
					strcat(writingCommand,">> ");
					strcat(writingCommand,file);
					system(writingCommand);
					
                }
                else
                {
                     printf("Radioactive car: %d, Position on Bridge: %d, Queue: Right, Can car move: %d, IdCar: %d, Bridge: %d\n",
                      i,pointer->data->bridgePos,pointer->data->askContinue,pointer->data->carID,pointer->data->bridgeID);
					char completeCharArray [255];
					char writingCommand [255];
					char str[10];
					sprintf(str, "%d", pointer->data->bridgePos);
					strcpy(completeCharArray,str);
					strcat(completeCharArray,",");
					strcat(completeCharArray,"Radioactive");
					strcat(completeCharArray,",");
					strcat(completeCharArray,"right");
					strcat(completeCharArray,",");
					sprintf(str, "%d", pointer->data->carID);
					strcat(completeCharArray,str);
					strcat(completeCharArray,",");
					sprintf(str, "%d", pointer->data->bridgeID);
					strcat(completeCharArray,str);
					strcpy(writingCommand,"echo ");
					strcat(writingCommand,completeCharArray);
					strcat(writingCommand,">> ");
					strcat(writingCommand,file);
					system(writingCommand);
                }               

            }
            else
            {
                if(pointer->data->queueSide==LEFTQUEUE)
                {
                     printf("Normal car: %d, Position on Bridge: %d, Queue: Left, Can car move: %d, IdCar: %d, Bridge: %d\n", 
                        i,pointer->data->bridgePos,pointer->data->askContinue,pointer->data->carID,pointer->data->bridgeID);
					char completeCharArray [255];
					char writingCommand [255];
					char str[10];
					sprintf(str, "%d", pointer->data->bridgePos);
					strcpy(completeCharArray,str);
					strcat(completeCharArray,",");
					strcat(completeCharArray,"normalCar");
					strcat(completeCharArray,",");
					strcat(completeCharArray,"left");
					strcat(completeCharArray,",");
					sprintf(str, "%d", pointer->data->carID);
					strcat(completeCharArray,str);
					strcat(completeCharArray,",");
					sprintf(str, "%d", pointer->data->bridgeID);
					strcat(completeCharArray,str);
					strcpy(writingCommand,"echo ");
					strcat(writingCommand,completeCharArray);
					strcat(writingCommand,">> ");
					strcat(writingCommand,file);
					system(writingCommand);
                }
                else
                {
                     printf("Normal car: %d, Position on Bridge: %d, Queue: Right, Can car move: %d, IdCar: %d, Bridge: %d\n",
                      i,pointer->data->bridgePos,pointer->data->askContinue,pointer->data->carID,pointer->data->bridgeID);
					char completeCharArray [255];
					char writingCommand [255];
					char str[10];
					sprintf(str, "%d", pointer->data->bridgePos);
					strcpy(completeCharArray,str);
					strcat(completeCharArray,",");
					strcat(completeCharArray,"normalCar");
					strcat(completeCharArray,",");
					strcat(completeCharArray,"right");
					strcat(completeCharArray,",");
					sprintf(str, "%d", pointer->data->carID);
					strcat(completeCharArray,str);
					strcat(completeCharArray,",");
					sprintf(str, "%d", pointer->data->bridgeID);
					strcat(completeCharArray,str);
					strcpy(writingCommand,"echo ");
					strcat(writingCommand,completeCharArray);
					strcat(writingCommand,">> ");
					strcat(writingCommand,file);
					system(writingCommand);
                }   
               
            }
            
            pointer = pointer->next;            
        }
    }
}

