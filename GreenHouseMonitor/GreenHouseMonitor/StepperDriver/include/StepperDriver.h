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



/**
  * @brief Initiates the Stepper Driver.
  * 
  * 
  * @param analogPin is the pin number used for the soil humidity sensor.
  * 
  * @return void
  * 
**/
void StepperInit();	

/**
  * @brief short description
  * 
  * Longer description
  * 
  * @param <parametername> <description>  .... i.e. analogPin is the pin number used for the soil humidity sensor.
  * 
  * @return <description> i.e. what is returned. for example: void
  * 
**/	
void DefaultReset();

/**
  * @brief short description
  * 
  * Longer description
  * 
  * @param <parametername> <description>  .... i.e. analogPin is the pin number used for the soil humidity sensor.
  * 
  * @return <description> i.e. what is returned. for example: void
  * 
**/	
void EnableMotor();

/**
  * @brief short description
  * 
  * Longer description
  * 
  * @param <parametername> <description>  .... i.e. analogPin is the pin number used for the soil humidity sensor.
  * 
  * @return <description> i.e. what is returned. for example: void
  * 
**/	
void DisableMotor();

/**
  * @brief short description
  * 
  * Longer description
  * 
  * @param <parametername> <description>  .... i.e. analogPin is the pin number used for the soil humidity sensor.
  * 
  * @return <description> i.e. what is returned. for example: void
  * 
**/	
void SetStepperMode(int mode);

/**
  * @brief short description
  * 
  * Longer description
  * 
  * @param <parametername> <description>  .... i.e. analogPin is the pin number used for the soil humidity sensor.
  * 
  * @return <description> i.e. what is returned. for example: void
  * 
**/	
void OpenWindow();

/**
  * @brief short description
  * 
  * Longer description
  * 
  * @param <parametername> <description>  .... i.e. analogPin is the pin number used for the soil humidity sensor.
  * 
  * @return <description> i.e. what is returned. for example: void
  * 
**/	
void CloseWindow();

/**
  * @brief short description
  * 
  * Longer description
  * 
  * @param <parametername> <description>  .... i.e. analogPin is the pin number used for the soil humidity sensor.
  * 
  * @return <description> i.e. what is returned. for example: void
  * 
**/	
void DriveStepper(int revolutions);

/**
  * @brief short description
  * 
  * Longer description
  * 
  * @param <parametername> <description>  .... i.e. analogPin is the pin number used for the soil humidity sensor.
  * 
  * @return <description> i.e. what is returned. for example: void
  * 
**/	
void SetDirection(/*struct Motor *motor,*/ int direction);

/**
  * @brief short description
  * 
  * Longer description
  * 
  * @param <parametername> <description>  .... i.e. analogPin is the pin number used for the soil humidity sensor.
  * 
  * @return <description> i.e. what is returned. for example: void
  * 
**/	
void CalibrateWindowOpening();


#endif /* STEPPERDRIVER_H_ */