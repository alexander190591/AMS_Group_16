 /*! \brief Low level driver for SPI.
 *			
 *	
 *	Filename:	./GreenHouseMonitor/SPIDriver/include/SPIDriver.c
 *	Created:	16-04-2020 08:32:41
 *	Author:		Tonni Lutze
 *
 */

  
  #include "../include/SPIDriver.h"



  //pointer variable to the port
  volatile uint8_t *spiPort;
  volatile uint8_t *spiDDR;

  



void SPI_Init(char port, int misoPin, int mosiPin, int ssPin, int clkPin)
{
	spiDDR = (	(port == 'a') | (port == 'A') ? &DDRA : 
				(port == 'b') | (port == 'B') ? &DDRB : 
				(port == 'c') | (port == 'C') ? &DDRC : 
				(port == 'd') | (port == 'D') ? &DDRD :
				(port == 'e') | (port == 'E') ? &DDRE :
				(port == 'f') | (port == 'F') ? &DDRF :
				(port == 'g') | (port == 'G') ? &DDRG :
				(port == 'h') | (port == 'H') ? &DDRH : NULL);

	spiPort = (	(port == 'a') | (port == 'A') ? &PORTA : 
				(port == 'b') | (port == 'B') ? &PORTB :
				(port == 'c') | (port == 'C') ? &PORTC : 
				(port == 'd') | (port == 'D') ? &PORTD : 
				(port == 'e') | (port == 'E') ? &PORTE : 
				(port == 'f') | (port == 'F') ? &PORTF : 
				(port == 'g') | (port == 'G') ? &PORTG :
				(port == 'h') | (port == 'H') ? &PORTH : NULL);


	*spiDDR |=  (1 << ssPin);						//	Selecting pin for Cable Select / Slave Select
	*spiDDR |=  (1 << mosiPin);						//	Selecting pin for MOSI
	*spiDDR &= ~(1 << misoPin);						//	Selecting pin for MISO
	*spiDDR |=  (1 << clkPin);						//	Selecting pin for Clock

	
	SPCR = (	(0 << SPR0) | 					//	SPI Clock Rate 
				(1 << SPR1)	| 					//	SPI Clock Rate
				(0 << CPHA)	|					//	Clock Phase (0:leading / 1:trailing edge sampling)
				(0 << CPOL)	|					//	Clock Polarity (0:SCK low / 1:SCK hi when idle)
				(1 << MSTR)	|					//	1:Master/0:Slave select
				(0 << DORD)	|					//	Data Order (0:MSB first / 1:LSB first)
				(1 << SPE)	|					//	SPI Enable
				(0 << SPIE)	);					//	SPI Interupt Enable

	SPSR =		0;//(1 << SPI2X);					//	Double Clock Rate / Should be 0 i guess
}




void SPI_SlaveSelect(int ssPin, bool enable){

	if (enable) {
		*spiPort &= ~(1 << ssPin);
//		SendDebugMessage("SS Enabled!");
	}
	else{
		*spiPort |=  (1 << ssPin);
//		SendDebugMessage("SS disabled!");
	}
}


unsigned char SPI_Rx(){
	
	unsigned char data; 

	SPDR = 0xff;						//	Starting transmit.
	while (!(SPSR & (1 << SPIF))) 	{}	//	Waiting for transmit complete flag.
	data = SPDR;						//	Clearing data, for next transmit.
	return data;						//	Returning data.
}

void SPI_Tx(unsigned char data){

	unsigned char dummy;

	SPDR = data;						//	Starting transmit.
	while (!(SPSR & (1 << SPIF))) {}	//	Waiting for transmit complete flag.
	dummy = SPDR;						//	Clearing data, for next transmit. 
}


unsigned char SPI_CycleByte(unsigned char inData){
	
	unsigned char outData;

	SPDR = inData;						//	Starting transmit.
	while (!(SPSR & (1 << SPIF))) {}	//	Waiting for transmit complete flag.
	outData = SPDR;						//	Clearing data, for next transmit.
	return outData;
}
