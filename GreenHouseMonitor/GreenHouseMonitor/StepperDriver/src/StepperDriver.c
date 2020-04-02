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
	
	STEPPER_MODE_DDR	|= (1 << STEPPER_MS1);
	STEPPER_MODE_DDR	|= (1 << STEPPER_MS2);
	STEPPER_MODE_DDR	|= (1 << STEPPER_MS3);

	//	Setting Stepper control pins as output
	STEPPER_EN_DDR		|= (1 << STEPPER_EN);
	STEPPER_DIR_DDR		|= (1 << STEPPER_DIR);
	STEPPER_STEP_DDR	|= (1 << STEPPER_STEP);

	

// 
// 	DDRF &= ~(1 << 1);
// 	DDRH |= (1 << 5);

	
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
		
	SINGLE_STEP_OFF;		//	Set Step Pin Low 	
	SetDirection(OPEN);		//	Default direction will be OPEN
	SetStepperMode(5);		//	I want my default as 1/16 Microstep mode (Mode 5 ( H H H )) : 
	DisableMotor();			//	Disabling until we actually need the motor
}


void SetStepperMode(int mode){

	switch (mode){
		case 1:	//	Mode: Full	( L L L )
			SINGLE_STEP_OFF;
			STEPPER_MODE_PORT	&= ~(1 << STEPPER_MS1);
			STEPPER_MODE_PORT	&= ~(1 << STEPPER_MS2);
			STEPPER_MODE_PORT	&= ~(1 << STEPPER_MS3);
			stepperMode = 1;
			break;
		case 2:	//	Mode: Half	( H L L )
			SINGLE_STEP_OFF;
			STEPPER_MODE_PORT	|=  (1 << STEPPER_MS1);
			STEPPER_MODE_PORT	&= ~(1 << STEPPER_MS2);
			STEPPER_MODE_PORT	&= ~(1 << STEPPER_MS3);
			stepperMode = 2;
			break;
		case 3:	//	Mode: 1/4 Microstep	( L H L )
			SINGLE_STEP_OFF;
			STEPPER_MODE_PORT	&= ~(1 << STEPPER_MS1);
			STEPPER_MODE_PORT	|=  (1 << STEPPER_MS2);
			STEPPER_MODE_PORT	&= ~(1 << STEPPER_MS3);
			stepperMode = 3;
			break;
		case 4:	//	Mode: 1/8 Microstep	( L L H )
			SINGLE_STEP_OFF;
			STEPPER_MODE_PORT	|=  (1 << STEPPER_MS1);
			STEPPER_MODE_PORT	|=  (1 << STEPPER_MS2);
			STEPPER_MODE_PORT	&= ~(1 << STEPPER_MS3);
			stepperMode = 4;
			break;
		case 5:	//	Mode: 1/16 Microstep	( H H H )
			SINGLE_STEP_OFF;
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
	SetDirection(OPEN);
	SetStepperMode(5);
	EnableMotor();	
	if (!isWindowOpen) { DriveStepper(revolutions); }
	isWindowOpen = true;
	DisableMotor();
}



void CloseWindow()
{
	int revolutions = 1;
	SetDirection(CLOSE);
	SetStepperMode(5);
	EnableMotor();
	if (isWindowOpen) { DriveStepper(revolutions); }
	isWindowOpen = false;
	DisableMotor();
}


void SetDirection(/*struct Motor *motor,*/ int direction){
	/*
	Rotations: 
	OPEN  =  1 = Clockwise
	CLOSE = -1 = Widdershins / Counter Clockwise
	*/
	if		(direction == OPEN)		{ DIRECTION_CLOCKWISE; }		//	Clockwise
	else if (direction == CLOSE)	{ DIRECTION_WIDDERSHINS; }		//	Widdershins
}

void EnableMotor(){
	MOTOR_ENABLE;
}

void DisableMotor(){
	MOTOR_DISABLE;
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
	SINGLE_STEP_OFF;

	//	Calculating the number of steps to complete an entire revolution
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

	//	Performing calculated steps
	for (int i = 0; i<steps; i++){
		//	Setting Step Pin HIGH on for taking a single step
		SINGLE_STEP_ON;

		//	Choosing apropriate delay, based on step mode.
			 if (stepperMode == 1) { _delay_us(DELAY_FULL_STEP); }
		else if (stepperMode == 2) { _delay_us(DELAY_HALF_STEP); }
		else if (stepperMode == 3) { _delay_us(DELAY_QUART_STEP); }
		else if (stepperMode == 4) { _delay_us(DELAY_EIGHT_STEP); }
		else if (stepperMode == 5) { _delay_us(DELAY_SIXTEENTH_STEP); }

		//	Setting Step Pin LOW after taking a single step
		SINGLE_STEP_OFF;
		//	Assuring an appropriate delay after finished step, based on step mode.
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