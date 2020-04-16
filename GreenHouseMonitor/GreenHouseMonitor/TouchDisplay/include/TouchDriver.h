/*
 * TouchDriver.h
 *
 * Created: 26-03-2020 09:35:22
 *  Author: Sebastian Folsach
 */ 

#include "../../DisplayDriver/include/TFTdriver.h"

#ifndef TOUCHDRIVER_H_
#define TOUCHDRIVER_H_

void TouchSetup();
void Setup();
void sendCommand(unsigned char command);



#endif /* TOUCHDRIVER_H_ */