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
#include <avr/interrupt.h>
#include <stdbool.h>

void TouchSetup();
void Setup();
int getData();
void setData();
//void sendCommand(unsigned char command);


#endif /* TOUCHDRIVER_H_ */