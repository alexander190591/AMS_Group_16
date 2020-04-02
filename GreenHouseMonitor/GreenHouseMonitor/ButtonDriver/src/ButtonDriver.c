 /*! \brief Low level driver for analog buttons.
 *	
 *			Description here
 *
 *
 *	
 *	Filename:	ButtonDriver.c
 *	Path:		./GreenHouseMonitor/ButtonDriver/src
 *	Created:	02-04-2020 07:52:49
 *	Author:		Tonni Lutze
 *	Major change #1:			
 *	Major change #2:
 */


 #include "../include/ButtonDriver.h"

 
 void InitButtons(){

	

	//	Setting momentary switches as input
 	STEPPER_BTN_DDR		&=	~(1 << STEPPER_BTN_OPENED);
 	STEPPER_BTN_DDR		&=	~(1 << STEPPER_BTN_CLOSED);

	//	Tying pins to pullups to make pins high
	STEPPER_BTN_PORT	|=	 (1 << STEPPER_BTN_OPENED);
	STEPPER_BTN_PORT	|=	 (1 << STEPPER_BTN_CLOSED);
 }



 unsigned char MntSwitchOpened() { return WINDOW_FULLY_OPEN; }

 unsigned char MntSwitchClosed() { return WINDOW_FULLY_CLOSED; }

