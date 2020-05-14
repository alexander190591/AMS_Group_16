/*
 * TouchDriver.c
 *
 * Created: 26-03-2020 09:35:36
 *  Author: Sebastian Folsach
 */ 
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




////////////////////////
// Pubkuc  functioner //
//     og variable    //
////////////////////////

/**
<A short one line description>

<Longer description>
<May span multiple lines or paragraphs as needed>

@param  No parameters
@return No return value (void)
*/
void Setup(){
	

	
	
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
		
}


void TouchSetup(){	
	
	CS_PORT &= ~(1<<TOUCH_CS); //Low
	
	_NOP();
	
	
	sendCommand(0b11010000);	//Sender commando til at læse X-koordinat
								//  fordi A2 = 0
								//		  A1 = 0
								//		  A0 = 1
	
	
	readDataX();
	
	
	sendCommand(0b00110000);	//Sender commando til at læse Y-koordinat
								//  fordi A2 = 1
								//		  A1 = 0
								//		  A0 = 1

	readDataY();
	
	
	clockPulse();

	CS_PORT |= (1<<TOUCH_CS); //High
	

	
}

int getData(){
	if((1000<_DataX) && (_DataX<2048)){
		if((0<_DataY) && (_DataY<1000)){
			return 1;
		}
	} else{
		return 0;
	}
}

void setData(){
	_DataY = 0;
	_DataX = 0;
}

void sendCommand(unsigned char command){
	
	for (int i = 7; i>0; i--)
	{
		DIN_PORT = ((1&(command >> i))<<TOUCH_IN);
		clockPulse();
	
	}
	DIN_PORT = ((1&(command))<<TOUCH_IN);
	clockPulse();
	
	DIN_PORT &= ~(1<<TOUCH_IN);
	
	
}





//Interrupt routine

ISR(INT4_vect){

	
	TCH_SCRN_EIMSK &=  ~(1<<TCH_SCRN_INT);
	
	TouchSetup();

	
	CS_PORT |= (1<<TOUCH_CS); //High

	TCH_SCRN_EIMSK |=  (1<<TCH_SCRN_INT);
	
	DisplayInit();

	
}


 

