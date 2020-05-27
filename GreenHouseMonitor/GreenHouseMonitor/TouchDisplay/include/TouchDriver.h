/*
 * TouchDriver.h
 *
 * Created: 26-03-2020 09:35:22
 *  Author: Sebastian Folsach
 */ 
#ifndef TOUCHDRIVER_H_
#define TOUCHDRIVER_H_



#include "../../DisplayDriver/include/TFTdriver.h"
#include "../../DisplayDriver/include/DisplayControl.h"
#include "../../StepperDriver/include/StepperDriver.h"
#include "../../ButtonDriver/include/ButtonDriver.h"
#include <avr/interrupt.h>


//void TouchSetup();
void SetupTouch();
int getData();
void setData();
//void sendCommand(unsigned char command);


#endif /* TOUCHDRIVER_H_ */