/*
 * SebastianMain.c
 *
 * Created: 26-03-2020 08:43:46
 *  Author: Alexander
 */ 
#include "MainFiles.h"
#include "../TouchDisplay/include/TouchDriver.h"

void SebastianMain()
{
	/* Replace with your application code */
	while (1)
	{
		// Initialize the display
		DisplayInit();
		//All pixels white (background)
		FillRectangle(0,0,320,240,31,63,31);
		// Draw red parts of danish flag
		FillRectangle(0,140,100,100,31,0,0);
		FillRectangle(0,0,100,100,31,0,0);
		FillRectangle(140,0,320-140,100,31,0,0);
		FillRectangle(140,140,320-140,100,31,0,0);
		Setup();
		//DisplayOn();
		//_delay_ms(1000);
		//DisplayOff();
		//_delay_ms(1000);
		//DisplayOn();
		while(1)
		{
			//DisplayOn();
			//_delay_ms(1000);
			//DisplayOff();
			//_delay_ms(1000);
			TouchSetup();
		}
	}
}