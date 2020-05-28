/*! \brief Low level driver for analog buttons.
 *	
 *	Filename:	./GreenHouseMonitor/ButtonDriver/include/ButtonDriver.h
 *	Created:	02-04-2020 07:52:49
 *	Author:		Tonni Lutze
 *
 *	
 */

 //#define F_CPU 16000000
 #pragma once
 #include <avr/io.h>
 #include <util/delay.h>
 #include "../../defines.h"


 #define WINDOW_FULLY_OPEN		!((STEPPER_READ_BTN_OPENED & (1 << STEPPER_BTN_OPENED)) == 0)
 #define WINDOW_FULLY_CLOSED	!((STEPPER_READ_BTN_CLOSED & (1 << STEPPER_BTN_CLOSED)) == 0)



 /**
  * @brief Initiates the Button Driver.
  * 
  * 
  * @param None.
  * 
  * @return void
  * 
**/
 void InitButtons();


 /**
  * @brief monitors a pin to check if end switch has been pressed.
  * 
  * 
  * @param None.
  * 
  * @return unsigned char - returns 0 or 1
  * 
**/
 unsigned char MntSwitchOpened();


 /**
  * @brief monitors a pin to check if switch has been pressed.
  * 
  * 
  * @param None.
  * 
  * @return unsigned char - returns 0 or 1
  * 
**/
 unsigned char MntSwitchClosed();

