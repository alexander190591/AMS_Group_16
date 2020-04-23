/*
 * TouchDriver.c
 *
 * Created: 26-03-2020 09:35:36
 *  Author: Sebastian Folsach
 */ 
#include <avr/io.h>
#include <avr/cpufunc.h>
#include <util/delay.h>
#include "../include/TouchDriver.h"
#include "../../defines.h"


//Define Ports
#define CLK_PORT	PORTH
#define CS_PORT		PORTE
#define DIN_PORT	PORTG
#define DOUT_PORT	PORTE
#define IRQ_PORT	PORTE
int _Data = 0;


void Setup(){
	
	//Setting Arduino outputs
	DDRE |= (1<<TOUCH_CS);
	DDRG |= (1<<TOUCH_IN);
	DDRH |= (1<<TOUCH_CLK);
	
	//Setting Arduino inputs	
	DDRE &= ~(1<<TOUCH_OUT);
	DDRE &= ~(1<<TOUCH_IRQ);
	//DDRG |= 0b0010000;

	_NOP();
	_NOP();
}


void TouchSetup(){	
	CS_PORT &= ~(1<<TOUCH_CS); //Low
	
	sendCommand(0b11010000);
	
	_NOP();
	_NOP();
	_NOP();
	_NOP();
	CLK_PORT |= (1<<TOUCH_CLK); //High
	_NOP();
	_NOP();
	_NOP();
	_NOP();
	CLK_PORT |= (0<<TOUCH_CLK); //Low
	
	if(readData() > 0){
		DisplayOff();
		_delay_ms(1000);
		DisplayOn();
		_delay_ms(1000);
	}
	CS_PORT |= (1<<TOUCH_CS); //High
	
	
}

void sendCommand(unsigned char command){
	
	for (int i = 7; i>0; i--)
	{
		DIN_PORT |= ((1&(command >> i))<<TOUCH_IN);
		clockPulse();
	}
	
	DIN_PORT &= ~(1<<TOUCH_IN);
	
	/*for(int i = 0; i<8; i++){
		T4Delay();
		
	}*/
	
}
////////////////////////
// Private functioner //
//     og variable    //
////////////////////////

int readData(){
	_Data = 0;
	for(int i = 11; i>0; i--){
		_Data = (TOUCH_OUT << i);
		clockPulse();
	}
	for (int i = 0; i < 4; i++)
	{
		clockPulse();
	}
	return _Data;
}

void clockPulse(){
	_NOP();
	_NOP();
	_NOP();
	_NOP();
	CLK_PORT |= (1<<TOUCH_CLK); //High
	//_delay_us(200);
	_NOP();
	_NOP();
	_NOP();
	_NOP();
	CLK_PORT &= ~(1<<TOUCH_CLK); //Low
}

/*void T4Delay(){
	TCNT4 = 
}
*/

//Interrupt routine

ISR(INT4_vect){
	DisplayOff();
	_delay_ms(1000);
	DisplayOn();
}





 

