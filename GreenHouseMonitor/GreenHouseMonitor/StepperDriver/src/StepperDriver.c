 /*! \brief Low level driver for the Big Easy Stepper Motor Driver Module.
 *			
 *			
 *
 *	
 *	
 *	Filename:	StepperDriver.c
 *	Path:		./StepperDriver/src
 *	Created:	26-03-2020 09:32:41
 *	Author:		Tonni Lutze
 *
 *	Major change #1:
 *	Major change #2:
 */

 #include "../include/StepperDriver.h"

 /*
 
 Stepping modes: 
 Controlled by MS1, MS2 and MS3 

						MS1	MS2	MS3
 1	Full Step		:	L	L	L
 2	Half Step		:	H	L	L
 3	1/4 Microstep	:	L	H	L
 4	1/8 Microstep	:	H	H	L
 5	1/16 Microstep	:	H	H	H


 */





void StepperInit()
{
	if (!isInitialised){
	
	isWindowOpen = false;
	
	//	Setting Stepper mode pins as output
	
	STEPPER_MODE_DDR |= (1 << STEPPER_MS1);
	STEPPER_MODE_DDR |= (1 << STEPPER_MS2);
	STEPPER_MODE_DDR |= (1 << STEPPER_MS3);

	//	Setting Stepper control pins as output
	STEPPER_CTL_DDR |= (1 << STEPPER_EN);
	STEPPER_CTL_DDR |= (1 << STEPPER_DIR);
	STEPPER_CTL_DDR |= (1 << STEPPER_STEP);

	//	Setting End-switches as input
	STEPPER_BTN_DDR &= ~(1 << STEPPER_BTN_OPENED);
	STEPPER_BTN_DDR &= ~(1 << STEPPER_BTN_CLOSED);

	//DDRF &= ~(1 << 1);
	//DDRH |= (1 << 5);

	
	DefaultReset();
	isInitialised = true;
	}
}



// void SetPin(int pin_, int state_){
// 
// 	if		(state_ == HIGH )	{ return |=  ( 1 << pin_ );	}
// 	else if (state_ == LOW)		{ return &= ~( 1 << pin_ );	}
// 	else return NULL
// }


void DefaultReset(){
	
	//	I want my default as 1/16 Microstep mode (Mode 5 ( H H H )) : 
	//STEPPER_CTL_PORT	= SetPin(STEP_BIT, LOW);
	
	STEPPER_CTL_PORT	&= ~(1 << STEPPER_STEP);	//	Set Step Low 	
	SetDirection(OPEN);
	SetStepperMode(5);
	DisableMotor();								//	Disabling until we actually need the motor

}


void SetStepperMode(int mode){

	switch (mode){

		case 1:	//	Mode: Full	( L L L )
			STEPPER_CTL_PORT	&= ~(1 << STEPPER_STEP);
			STEPPER_MODE_PORT	&= ~(1 << STEPPER_MS1);
			STEPPER_MODE_PORT	&= ~(1 << STEPPER_MS2);
			STEPPER_MODE_PORT	&= ~(1 << STEPPER_MS3);
			stepperMode = 1;
			break;
		case 2:	//	Mode: Half	( H L L )
			STEPPER_CTL_PORT	&= ~(1 << STEPPER_STEP);
			STEPPER_MODE_PORT	|=  (1 << STEPPER_MS1);
			STEPPER_MODE_PORT	&= ~(1 << STEPPER_MS2);
			STEPPER_MODE_PORT	&= ~(1 << STEPPER_MS3);
			stepperMode = 2;
			break;
		case 3:	//	Mode: 1/4 Microstep	( L H L )
			STEPPER_CTL_PORT	&= ~(1 << STEPPER_STEP);
			STEPPER_MODE_PORT	&= ~(1 << STEPPER_MS1);
			STEPPER_MODE_PORT	|=  (1 << STEPPER_MS2);
			STEPPER_MODE_PORT	&= ~(1 << STEPPER_MS3);
			stepperMode = 3;
			break;
		case 4:	//	Mode: 1/8 Microstep	( L L H )
			STEPPER_CTL_PORT	&= ~(1 << STEPPER_STEP);
			STEPPER_MODE_PORT	|=  (1 << STEPPER_MS1);
			STEPPER_MODE_PORT	|=  (1 << STEPPER_MS2);
			STEPPER_MODE_PORT	&= ~(1 << STEPPER_MS3);
			stepperMode = 4;
			break;
		case 5:	//	Mode: 1/16 Microstep	( H H H )
			STEPPER_CTL_PORT	&= ~(1 << STEPPER_STEP);
			STEPPER_MODE_PORT	|=  (1 << STEPPER_MS1);
			STEPPER_MODE_PORT	|=  (1 << STEPPER_MS2);
			STEPPER_MODE_PORT	|=  (1 << STEPPER_MS3);
			stepperMode = 5;
			break;
		default:
			break;
	}
}

void OpenWindow()
{
	int revolutions = 1;
		
	if (!isWindowOpen)
	{
		StepperInit();
		SetDirection(OPEN);
		SetStepperMode(4);
		EnableMotor();
		DriveStepper(revolutions);
		isWindowOpen = true;
		DisableMotor();
	}
}



void CloseWindow()
{
	int revolutions = 10;
	
	if (isWindowOpen)
	{
		StepperInit();
		SetDirection(CLOSE);
		SetStepperMode(4);
		EnableMotor();
		DriveStepper(revolutions);
		isWindowOpen = false;
		DisableMotor();
	}
}


void SetDirection(/*struct Motor *motor,*/ int direction){
	/*
	Rotations: 
	OPEN  =  1 = Clockwise
	CLOSE = -1 = Widdershins / Counter Clockwise
	*/
	if		(direction == OPEN)	{ STEPPER_CTL_PORT |=  (1 << STEPPER_DIR); }		//	Clockwise
	else if (direction == CLOSE)	{ STEPPER_CTL_PORT &= ~(1 << STEPPER_DIR); }		//	Widdershins
}

void EnableMotor(/*struct Motor *motor*/){
	STEPPER_CTL_PORT &=	~(1 << STEPPER_EN);
}

void DisableMotor(/*struct Motor *motor*/){
	STEPPER_CTL_PORT |=	(1 << STEPPER_EN);
}



void DriveStepper(int revolutions){

/*
For the sake of simplicity we only operate with complete revolutions. 
One complete revolution is 360 degrees divided by the degree per step if the stepper 
Our stepper has a rating of 0.9 degrees per step
hence: 360 degree / (0,9 degree / Step ) = 400 steps
If we're microstepping we need to multiply the steps by the inverse of the microstep fraction. i.e.
If the mode is set to 1/16 microstep: 
360 degree / (0,9 degree / Step ) * 16 = 6400 steps
*/


int steps = 0;

//	Setting Step low to prepare.
	STEPPER_CTL_PORT &= ~(1 << STEPPER_STEP);
	
	switch (stepperMode){
		case 1:
			steps = (STEP_REVOLUTION * 1 *	revolutions);
			break;
		case 2:
			steps = (STEP_REVOLUTION * 2 *	revolutions);
			break;
		case 3:
			steps = (STEP_REVOLUTION * 4 *	revolutions);
			break;
		case 4:
			steps = (STEP_REVOLUTION * 8 *	revolutions);
			break;
		case 5:
		default:
			steps = (STEP_REVOLUTION * 16 * revolutions);
			break;
	}

	for (int i = 0; i<steps; i++){
		SINGLE_STEP_ON;

			 if (stepperMode == 1) { _delay_us(DELAY_FULL_STEP); }
		else if (stepperMode == 2) { _delay_us(DELAY_HALF_STEP); }
		else if (stepperMode == 3) { _delay_us(DELAY_QUART_STEP); }
		else if (stepperMode == 4) { _delay_us(DELAY_EIGHT_STEP); }
		else if (stepperMode == 5) { _delay_us(DELAY_SIXTEENTH_STEP); }

		SINGLE_STEP_OFF;
			 if (stepperMode == 1) { _delay_us(DELAY_FULL_STEP); }
		else if (stepperMode == 2) { _delay_us(DELAY_HALF_STEP); }
		else if (stepperMode == 3) { _delay_us(DELAY_QUART_STEP); }
		else if (stepperMode == 4) { _delay_us(DELAY_EIGHT_STEP); }
		else if (stepperMode == 5) { _delay_us(DELAY_SIXTEENTH_STEP); }
	}
}

void CalibrateWindowOpening(){

	bool isWindowClosed, endStopReached = false;
	int revolutionCount = 0;
	
	//	First we want to make sure the window is fully closed
	SetDirection(CLOSE);
	SetStepperMode(4);
	EnableMotor();
	while (!isWindowClosed)
	{
		if (!(~PINF & (1 << STEPPER_BTN_CLOSED)))
		{
			isWindowClosed = true;
		}

		DriveStepper(1);
	}

	//	The window should be closed at this point
	//	Now we run the stepper forwards until it hits the end switch, while it does we'll count the number of revolutions it takes to open fully
	SetDirection(OPEN);
	while (!endStopReached)
	{
		if (!(~PINF & (1 << STEPPER_BTN_OPENED)))
		{
			endStopReached = true;
		}
		DriveStepper(1);
		revolutionCount ++;		
	}
	//	Now we should know the number of revolutions it took to open the window fully, this value can be saved and used to open the window in percentages or via an PID in conjunction with temperature measurements
	
	maxNbrRevolutions = revolutionCount;
}