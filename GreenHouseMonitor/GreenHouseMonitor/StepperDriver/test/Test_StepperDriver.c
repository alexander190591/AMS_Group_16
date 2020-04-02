 /*! \brief Test code for testing Stepperdriver.h/.c
 *			
 *			
 *
 *	
 *	
 *	Filename:	Test_StepperDriver.c
 *	Path:		./GreenHouseMonitor/StepperDriver/test
 *	Created:	02-04-2020 13:22:12
 *	Author:		Tonni Lutze
 *
 *	Major change #1:
 */

 #include <avr/io.h>
 #define F_CPU 16000000UL
 #include <util/delay.h>
 
 #include "../include/StepperDriver.h"
 
//  #define BAUD 9600
//  #include <util/setbaud.h> 

 


void TestStepperDriver()
{

	//	TEMPORARY STUFF to init LED on pin A7
	DDRF	|= (1 << PF7);
	#define TEST_LED_ON		(PORTF |=	 (1 << PF7))
	#define TEST_LED_OFF	(PORTF &=	~(1 << PF7))
	//	TEMPORARY STUFF END

	// Init
	StepperInit();
	CalibrateWindowOpening();
	
	for (int i = 0; i < maxNbrRevolutions; i++)
	{
		
		PORTF |= 0xF0; // 4 output bits high
		_delay_ms(500);
		PORTF &= ~0xF0; // 4 output bits low
		_delay_ms(500);
	}


// 	for (int i = 0; i<5;i++)
// 	{
// 		
// 		//	Opening window.
// 		OpenWindow();
// 		
// 		_delay_ms(100);
// 
// 		//	Closing window.
//  		CloseWindow();
//  
//  		_delay_ms(100);
// 	}

	

	
	//	Creating objects:

	
	// 	struct Window	*windowPtr,	windowA;
	// 	windowPtr	= &windowA;
	//
	// 	OpenWindow(&windowA);


	//unsigned char mask;
	//mask = (1 << 7);


	//bool isMotorRunning = false;


// 	while (1)
// 	{
//
//  			isMotorRunning = true;
//
//  			if (!(~PINF & mask))
//  			{
//  				PORTH |=  (1 << 5);
//  				isMotorRunning = false;
//
//  			}
//
//  			if (isMotorRunning)
//  			{
//  				OpenWindow();
//  				PORTH &=  ~(1 << 5);
//  				isWindowOpen = false;
//  				isMotorRunning = true;
//
//  			}
//
// 		//PORTF = 0b00111111;
//
// 	}

}
