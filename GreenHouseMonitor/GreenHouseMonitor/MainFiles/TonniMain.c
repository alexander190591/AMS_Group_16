/*
 * TonniMain.c
 *
 * Created: 26-03-2020 08:44:17
 *  Author: Alexander
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>


#include "MainFiles.h"
#include "../StepperDriver/include/StepperDriver.h"
#include "../StepperDriver/test/Test_StepperDriver.h"
#include "../ButtonDriver/include/ButtonDriver.h"

unsigned char SW_Status(){
	return (~PINF);
}


void TonniMain(){
	
// 	TestStepperDriver();

	
	InitButtons();
		

// 		
// 	TestStepperDriver();

}