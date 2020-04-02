/*! \brief Low level driver for analog buttons.
 *	
 *			Description here
 *
 *
 *	
 *	Filename:	ButtonDriver.h
 *	Path:		./ButtonDriver/include
 *	Created:	02-04-2020 07:52:49
 *	Author:		Tonni Lutze
 *
 *	Major change #1:
 *	Major change #2:
 */

 #define F_CPU 16000000

 #include <avr/io.h>
 #include <util/delay.h>

 #include "../../defines.h"


 #define WINDOW_FULLY_OPEN		((STEPPER_READ_BTN_OPENED & (1 << STEPPER_BTN_OPENED)) == 0)
 #define WINDOW_FULLY_CLOSED	((STEPPER_READ_BTN_CLOSED & (1 << STEPPER_BTN_CLOSED)) == 0)




 void InitButtons();
 unsigned char MntSwitchOpened();
 unsigned char MntSwitchClosed();

