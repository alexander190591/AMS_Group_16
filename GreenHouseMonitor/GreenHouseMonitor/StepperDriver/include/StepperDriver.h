/*
 * StepperDriver.h
 *
 * Created: 26-03-2020 09:32:41
 *  Author: Tonni
 */ 


 /*! \brief Low level driver for the Big Easy Stepper Motor Driver Module.
 *	
 *	Filename: 
 *	Created: 
 *	
 */

 #include <avr/io.h>
 #define F_CPU 16000000
 #include <util/delay.h>
 #include <stdbool.h>
 #include "../../defines.h"


#ifndef STEPPERDRIVER_H_
#define STEPPERDRIVER_H_

#define STEP_DEGREE		0.9
#define STEP_REVOLUTION	(360 / STEP_DEGREE)
#define SINGLE_STEP_ON	(STEPPER_CTL_PORT |=   (1 << STEPPER_STEP))
#define SINGLE_STEP_OFF	(STEPPER_CTL_PORT &=  ~(1 << STEPPER_STEP))

#define END_SWITCH_CLOSED	(PINA & SW_CLOSE_BIT)
#define END_SWITCH_OPEN		(PINA & SW_OPEN_BIT)

#define DELAY_FULL_STEP			300
#define DELAY_HALF_STEP			140
#define DELAY_QUART_STEP		80
#define DELAY_EIGHT_STEP		50
#define DELAY_SIXTEENTH_STEP	20

// 
// #define OPEN  (STEPPER_CTL_PORT |=  (1 << DIR_BIT)
// #define CLOSE (STEPPER_CTL_PORT &= ~(1 << DIR_BIT)

int stepperMode; 
bool isInitialised; 
bool isWindowOpen;
int maxNbrRevolutions;


struct Motor{
	bool isEnabled;
	int direction;	
};



struct Window{
	bool	isOpen;
	//int		maxNbrRevolutions;
	int		currNbrRevolutions;

// 	struct Motor *motorPTR,	motor;
// 	motorPTR = &motor;
};



//	For Initializing the Stepper Driver
void StepperInit();	
//	
void DefaultReset();

void EnableMotor();

void DisableMotor();


void SetStepperMode(int mode);

void OpenWindow();

void CloseWindow();

void DriveStepper(int revolutions);

void SetDirection(/*struct Motor *motor,*/ int dir);


#endif /* STEPPERDRIVER_H_ */