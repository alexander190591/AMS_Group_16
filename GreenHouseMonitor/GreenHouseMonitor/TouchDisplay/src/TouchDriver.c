/** 
  *	
  *	
  *	@file:		TouchDriver.c
  *	@path:		./GreenHouseMonitor/TouchDisplay/src
  *	@date:		26-03-2020 09:35:36
  *	@author:	Sebastian Folsach
  *
  *	@brief Driver for using touch functionality with screen having a XPT2046.
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
#include <avr/cpufunc.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../include/TouchDriver.h"
#include "../../defines.h"


//Define Ports
#define CLK_PORT	PORTH
#define CS_PORT		PORTE
#define DIN_PORT	PORTG
#define DOUT_PORT	PORTE
#define IRQ_PORT	PORTE
int _DataX = 0;
int _DataY = 0;


////////////////////////
// Private functioner //
//     og variable    //
////////////////////////


/**
  * @brief Function for reading the X-coordinate
  * 
  * This function reads the bit stream for each clock pulse and concatenates it up to have the complete value.
  * 
  * @param void
  * 
  * @return void
  * 
**/	
void readDataX(){
	_DataX = 0;
	for(int i = 12; i>0; i--){
		if(PINE & (1<<PINE5)){
			_DataX = (_DataX<<1) + 1;
		} else {
			_DataX = (_DataX<<1);
		}

		clockPulse();
	}
	for (int i = 0; i < 4; i++)
	{
		clockPulse();
	}
}



/**
  * @brief Function for reading the Y-coordinate
  *
  * This function reads the bit stream for each clock pulse and concatenates it up to have the complete value.
  * 
  * @param void
  * 
  * @return void
  * 
**/	
void readDataY(){
	_DataY = 0;
	for(int i = 12; i>0; i--){
		if(PINE & (1<<PINE5)){
			_DataY = (_DataY<<1) + 1;
		} else {
			_DataY = (_DataY<<1);
		}
		if(i>1)
			clockPulse();
	}
	for (int i = 0; i < 4; i++)
	{
		clockPulse();
	}
}



/**
  * @brief Function for making a clock pulse
  *
  * This function makes a clock pulse by waiting four "_NOP()" which is 250 ns and then switches state.
  * 
  * @param void
  * 
  * @return void
  * 
**/	
void clockPulse(){
	_NOP();
	_NOP();
	_NOP();
	_NOP();
	CLK_PORT |= (1<<TOUCH_CLK); //High

	_NOP();
	_NOP();
	_NOP();
	_NOP();
	CLK_PORT &= ~(1<<TOUCH_CLK); //Low
}



/**
  * @brief Function for sending command
  *
  * This function sends an 8-bit command to the XPT2046 about what it should send back
  * 
  * @param command is an unsigned char
  * 
  * @return void
  * 
**/	
void sendCommand(unsigned char command){
	
	for (int i = 7; i>0; i--)
	{
		if(((1&(command >> i))<<TOUCH_IN))
		DIN_PORT |= (1<<TOUCH_IN);
		else
		DIN_PORT &= ~(1<<TOUCH_IN);
		
		clockPulse();
		
	}
	
	if(((1&(command))<<TOUCH_IN))
	DIN_PORT |= (1<<TOUCH_IN);
	else
	DIN_PORT &= ~(1<<TOUCH_IN);
	
	clockPulse();
	
	DIN_PORT &= ~(1<<TOUCH_IN);
	
	
}

////////////////////////
// Public  functioner //
//     og variable    //
////////////////////////


void SetupTouch(){
	
	DisplayControlConstruct();
	
	
	//Setting Arduino outputs
	DDRE |= (1<<TOUCH_CS);
	DDRG |= (1<<TOUCH_IN);
	DDRH |= (1<<TOUCH_CLK);
	
	//Setting Arduino inputs	
	DDRE &= ~(1<<TOUCH_OUT);
	DDRE &= ~(1<<TOUCH_IRQ);

	_NOP();
	_NOP();
	
	//_delay_ms(1000)
	

	_NOP();
	_NOP();

	
	CS_PORT |= (1<<TOUCH_CS); //High
	
	
	
	TCH_SCRN_EICR |=   (1<<TCH_SCRN_ISC1);		//ISC41 == 1
	TCH_SCRN_EICR &=  ~(1<<TCH_SCRN_ISC0);		//ISC40 == 0
	
	TCH_SCRN_EIMSK |=  (1<<TCH_SCRN_INT);
	
	//Første box
	FillRectangle(0, 120, 80, (240-120), 0, 0, 0);
	FillRectangle(5, 125, 75, (240-130), 31, 63, 31);
	
	
	//Anden box
	FillRectangle(80, 120, 80, (240-120), 0, 0, 0);
	FillRectangle(85, 125, 75, (240-130), 31, 63, 31);
	
	//Tredje box
	FillRectangle(160, 120, 80, (240-120), 0, 0, 0);
	FillRectangle(165, 125, 75, (240-130), 31, 63, 31);
	
	//Fjerde box
	FillRectangle(240, 120, 80, (240-120), 0, 0, 0);
	FillRectangle(245, 125, 75, (240-130), 31, 63, 31);
	
	writeWindowBoxes();
	
		
}

/**
  * @brief Function for all XPT2046 communication
  *
  * This function initiates communication by pulling the chip select bit low sends an 8-bit command to the XPT2046 about what wanting the X-coordinate after which it reads the respons.
  *  
  * Then it send an 8-bit command to the XPT2046 about what wanting the Y-coordinate after which it reads the respons.
  *
  * @param command is an unsigned char
  * 
  * @return void
  * 
**/	
void TouchCommunication(){	
	
	CS_PORT &= ~(1<<TOUCH_CS); //Low
	
	_NOP();
	_NOP();
	
	
	sendCommand(0b10010010);	//Sender commando til at læse X-koordinat
								//  fordi A2 = 0
								//		  A1 = 0
								//		  A0 = 1
	
	
	readDataX();
	
	
	sendCommand(0b11010010);	//Sender commando til at læse Y-koordinat
								//  fordi A2 = 1
								//		  A1 = 0
								//		  A0 = 1

	readDataY();
	
	
	clockPulse();

	CS_PORT |= (1<<TOUCH_CS); //High
	

	
}
/**
  * @brief Function for getting the last pushed coordinates
  *
  * This function gives returns a representation for the place where the screen has been pushed
  *
  * @param void
  * 
  * @return int
  * 
**/	

int getData(){
	if (_DataY < 1000){
		if((0<_DataX) && (_DataX<500)){		//Open full window
			return 1;
		} else if ((500<_DataX) && (_DataX<1000))
		{
			return 2;						//Open a bit
		}
		else if ((1000<_DataX) && (_DataX<1500))
		{
			return 3;						//Close a bit
		}
		else if ((1500<_DataX) && (_DataX<2000))
		{
			return 4;						//Close full
		}
		else{
			return 0;
		}
	}
}



/**
  * @brief Function for wiping coordinate set.
  *
  * This function wipes the last read coordinate set.
  *
  * @param void
  * 
  * @return void
  * 
**/	
void setData(){
	_DataY = 0;
	_DataX = 0;
}





//Interrupt routine

/**
  * @brief Interrupt routine
  *
  * This is the interrupt routine that handles when an interrupt on PE4 is detected
  *
  * @param INT4_vect is a vector for the external interrupt
  * 
  * 
**/	
ISR(INT4_vect){
	_delay_ms(100);

	
	TCH_SCRN_EIMSK &=  ~(1<<TCH_SCRN_INT);
	
	TouchCommunication();

	
	CS_PORT |= (1<<TOUCH_CS); //High

	
			
			if(getData() == 1){						// Open full
				//updateWindowDisplay("op full");
				OpenWindow();
				setData();
			} else if (getData() == 2) {			//Open partly
				//updateWindowDisplay("op part");
				OpenWindowPct();
				setData();
			} else if (getData() == 3) {			//Close partly
				//updateWindowDisplay("cl part");
				CloseWindowPct();
				setData();
			} else if (getData() == 4) {			//Close fully
				//updateWindowDisplay("cl full");
				CloseWindow();
				setData();
			}
			
	EIFR |= 0x4;
	
	TCH_SCRN_EIMSK |=  (1<<TCH_SCRN_INT);

}


 

