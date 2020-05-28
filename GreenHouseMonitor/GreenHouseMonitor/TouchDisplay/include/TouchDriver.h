/** 
  *	
  *	
  *	@file:		TouchDriver.h
  *	@path:		./GreenHouseMonitor/TouchDisplay/include
  *	@date:		26-03-2020 09:35:22
  *	@author:	Sebastian Folsach
  *
  *	@brief Driver for using touch functionality with screen having a XPT2046.
  *	
  *	Description here
  *	
  *	
  *	
  *			
  *	Major change #1:
  *	
**/

#ifndef TOUCHDRIVER_H_
#define TOUCHDRIVER_H_



#include "../../DisplayDriver/include/DisplayControl.h"
#include "../../StepperDriver/include/StepperDriver.h"
#include "../../ButtonDriver/include/ButtonDriver.h"
#include <avr/interrupt.h>

/**
  * @brief Initiates the Touch Driver.
  * 
  * 
  * @param void.
  * 
  * @return void
  * 
**/
void SetupTouch();



#endif /* TOUCHDRIVER_H_ */