/*
 * TonniMain.c
 *
 * Created: 26-03-2020 08:44:17
 *  Author: Alexander
 */ 
#include "MainFiles.h"
#include "../StepperDriver/include/StepperDriver.h"
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>


unsigned char SW_Status(){
	return (~PINF);
}


void TonniMain()
{
	

// 	OpenWindow();
// 	_delay_ms(2000);
// 	CloseWindow();
// 
// 	_delay_ms(4000);
// 	OpenWindow();
// 	_delay_ms(2000);
// 	CloseWindow();







	

	//	Creating objects:

	
// 	struct Window	*windowPtr,	windowA;
// 	windowPtr	= &windowA;
// 	
// 	OpenWindow(&windowA); 


	//unsigned char mask; 
	//mask = (1 << 7);


	//bool isMotorRunning = false;



	/* Replace with your application code */
	while (1)
	{
// 		
// 			isMotorRunning = true;
// 		
// 			if (!(~PINF & mask))
// 			{
// 				PORTH |=  (1 << 5);
// 				isMotorRunning = false;
// 
// 			}
// 			
// 			if (isMotorRunning)
// 			{
// 				OpenWindow();
// 				PORTH &=  ~(1 << 5);
// 				isWindowOpen = false;
// 				isMotorRunning = true;
// 
// 			}
// 					
		

			
		//PORTF = 0b00111111;



		
	}
}