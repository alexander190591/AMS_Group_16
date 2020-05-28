/** 
  *	
  *	
  *	@file:		StepperDriver.h
  *	@path:		./GreenHouseMonitor/StepperDriver/include
  *	@date:		26-03-2020 09:32:41
  *	@author:	Tonni Lutze
  *
  *	@brief Low level driver for the Big Easy Stepper Motor Driver Module.
  *	
  *	Description here
  *	
  *	
  *	
  *			
  *	Major change #1:
  *	
**/

 #include <avr/io.h>
 //#define F_CPU 16000000
 //#include <util/delay.h>
 #include <stdbool.h>
 #include "../../defines.h"


#ifndef STEPPERDRIVER_H_
#define STEPPERDRIVER_H_

#pragma region DEFINES
//	Most of these defines only serves to limit the amount of code i need to write - 
//	no reason to write (STEPPER_STEP_PORT	|=   (1 << STEPPER_STEP)) a half dosen times if SINGLE_STEP_ON will do the same
#define STEP_DEGREE				0.9
#define STEP_REVOLUTION			(360 / STEP_DEGREE)
#define SINGLE_STEP_ON			(STEPPER_STEP_PORT	|=   (1 << STEPPER_STEP))
#define SINGLE_STEP_OFF			(STEPPER_STEP_PORT	&=  ~(1 << STEPPER_STEP))
#define DIRECTION_CLOCKWISE		(STEPPER_DIR_PORT	|=	 (1 << STEPPER_DIR))
#define DIRECTION_WIDDERSHINS	(STEPPER_DIR_PORT	&=	~(1 << STEPPER_DIR))
#define MOTOR_ENABLE			(STEPPER_EN_PORT	&=	~(1 << STEPPER_EN))
#define MOTOR_DISABLE			(STEPPER_EN_PORT	|=	 (1 << STEPPER_EN))

#define DELAY_FULL_STEP			300
#define DELAY_HALF_STEP			140
#define DELAY_QUART_STEP		80
#define DELAY_EIGHT_STEP		50
#define DELAY_SIXTEENTH_STEP	20

// #define END_SWITCH_CLOSED	(PINA & SW_CLOSE_BIT)
// #define END_SWITCH_OPEN		(PINA & SW_OPEN_BIT)


#pragma endregion DEFINES


// 
// #define OPEN  (STEPPER_CTL_PORT |=  (1 << DIR_BIT)
// #define CLOSE (STEPPER_CTL_PORT &= ~(1 << DIR_BIT)

int stepperMode; 
bool isInitialised; 
bool isWindowOpen;
double maxNbrRevolutions;


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



/**
  * @brief Initiates the Stepper Driver.
  * 
  * 
  * @param None.
  * 
  * @return void
  * 
**/
void StepperInit();	



/**
  * @brief Default Reset 
  * 
  * Resets settings to default i.e.
  *	
  *	SINGLE_STEP_OFF;		//	Set Step Pin Low
  *	SetDirection(OPEN);		//	Default direction will be OPEN
  *	SetStepperMode(5);		//	I want my default as 1/16 Microstep mode (Mode 5 ( H H H )) :
  *	DisableMotor();			//	Disabling until we actually need the motor
  * 
  * @param None. 
  * 
  * @return void
  * 
**/	
void DefaultReset();



/**
  * @brief Enables the Motor
  * 
  * 
  * 
  * @param None.
  * 
  * @return void
  * 
**/	
void EnableMotor();



/**
  * @brief Disable Motor
  * 
  * 
  * 
  * @param None. 
  * 
  * @return void
  * 
**/	
void DisableMotor();




/**
  * @brief set stepper mode
  * 
  * Setting the microstep resolution
  * 
  * @param int mode - Valid options: 1-5 where 1 = full step, 2 = halfstep, 3 = 1/4 microstep, 4 = 1/8 microstep, 5 = 1/16 microstep
  * 
  * @return void
  * 
**/	
void SetStepperMode(int mode);

/**
  * @brief Open Window
  * 
  * Drives the stepper to fully open the window. limit is reached when momentary switch is triggered. 
  * 
  * @param None. 
  * 
  * @return void.
  * 
**/	
void OpenWindow();

/**
  * @brief Close Window
  * 
  * Drives the stepper to fully Close the window. limit is reached when momentary switch is triggered. 
  * 
  * @param None. 
  * 
  * @return void.
  * 
**/	
void CloseWindow();

/**
  * @brief Drive stepper
  * 
  * this function drives the stepper in a preset direction for a chosen number of revolutions
  * 
  * @param int revolutions: valid options, any positive integer
  * 
  * @return void
  * 
**/	
void DriveStepper(int revolutions);

/**
  * @brief Set direction
  * 
  * Setting the direction the motor should turn. 
  * 
  * @param int direction - Valid options: OPEN and CLOSE (these are defined)
  * 
  * @return void
  * 
**/	
void SetDirection(/*struct Motor *motor,*/ int direction);

/**
  * @brief Calibrate window Opening
  * 
  * Runs a cycle where a window is first fully closed, and then fully opened to count the number of rotations needed
  *	to do this. this is used when opening the window some fraction of the possible max
  * 
  * @param None. 
  * 
  * @return void
  * 
**/	
void CalibrateWindowOpening();


#endif /* STEPPERDRIVER_H_ */