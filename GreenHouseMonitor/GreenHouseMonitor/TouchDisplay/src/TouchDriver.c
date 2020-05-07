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

void Setup(){
	
	//Setting Arduino outputs
	DDRE |= (1<<TOUCH_CS);
	DDRG |= (1<<TOUCH_IN);
	DDRH |= (1<<TOUCH_CLK);
	
	//Setting Arduino inputs	
	DDRE &= ~(1<<TOUCH_OUT);
	DDRE &= ~(1<<TOUCH_IRQ);
	//DDRG |= 0b0010000;
	
	EIMSK |= _BV(INT4);

	_NOP();
	_NOP();
}


void TouchSetup(){	
	CS_PORT &= ~(1<<TOUCH_CS); //Low
	
	sendCommand(0b10010111);	//Sender commando til at læse X-koordinat
								//  fordi A2 = 0
								//		  A1 = 0
								//		  A0 = 1
	
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
	
	readDataX();
	
	sendCommand(0b11010111);	//Sender commando til at læse Y-koordinat
								//  fordi A2 = 1
								//		  A1 = 0
								//		  A0 = 1
	
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
	
	readDataY();
	
	CS_PORT |= (1<<TOUCH_CS); //High
	
	if((1000<_DataX && _DataX<2048) && (1000<_DataY && _DataY<2048)){
		updateWindowDisplay("aaaaa");
	}
	
	
}

void sendCommand(unsigned char command){
	
	for (int i = 7; i>0; i--)
	{
		DIN_PORT = ((1&(command >> i))<<TOUCH_IN);
		clockPulse();
	}
	
	DIN_PORT &= ~(1<<TOUCH_IN);
	
	
}


//Interrupt routine

ISR(INT4_vect){
	_delay_ms(500);
	//if(readData() > 0){
		TouchSetup();
		_delay_ms(500);
		//_delay_ms(100);
		//_delay_ms(100);
	//}
}





 

