 /*! \brief Test code for testing Stepperdriver.h/.c
 *			
 *			
 *
 *	
 *	
 *	Filename:	Test_StepperDriver.c
 *	Path:		./StepperDriver/test
 *	Created:	02-04-2020 13:22:12
 *	Author:		Tonni Lutze
 *
 *	Major change #1:
 */


 #include "../include/StepperDriver.h"
 #include <util/delay.h>


void TestStepperDriver()
{

	// Init
	StepperInit();

	for (int i = 0; i<5;i++)
	{
		
		//	Opening window.
		OpenWindow();
		
		_delay_ms(100);

		//	Closing window.
 		CloseWindow();
 
 		_delay_ms(100);
	}

	

	
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
