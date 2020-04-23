/*
 * SebastianMain.c
 *
 * Created: 26-03-2020 08:43:46
 *  Author: Alexander
 */ 
#include "MainFiles.h"
#include <util/delay.h>
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
		
		updateWindowDisplay("aaaaa");
		_delay_ms(10000);
		windowControlDisplay(50,50);
		_delay_ms(20000);
		windowControlDisplay(50,50);
		_delay_ms(20000);
		windowControlDisplay(120,50);
		while(1)
		{
			//DisplayOn();
			_delay_ms(1000);
			//DisplayOff();
			//_delay_ms(1000);
			//TouchSetup();
		}
	}
}