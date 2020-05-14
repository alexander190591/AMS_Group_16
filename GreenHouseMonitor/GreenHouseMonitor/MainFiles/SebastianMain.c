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
		//DisplayOn();
		//All pixels white (background)
		FillRectangle(0,0,320,240,31,63,31);
		
		
		updateWindowDisplay("a");

		
		Setup();

		sei();
		while(1)
		{			
			if(getData() == 1){
				//DisplayInit();
				
				FillRectangle(0,0,320,240,31,63,31);
				updateWindowDisplay("AA");
				setData();
			}
		}
	}
}