 /*! \brief Low level driver for SPI.
 *			
 *			
 *
 *	
 *	
 *	Filename:	SPIDriver.h
 *	Path:		./GreenHouseMonitor/SPIDriver/include
 *	Created:	16-04-2020 08:32:41
 *	Author:		Tonni Lutze
 *
 *	Major change #1:
 */


 #include <string.h>
 #include <avr/io.h>
 #include <stdbool.h>

#ifndef SPIDRIVER_H_
#define SPIDRIVER_H_




void SPI_Init(char port, int misoPin, int mosiPin, int ssPin, int clkPin ); 
void SPI_SlaveSelect(int ssPin, bool enable);
void SPI_Tx(unsigned char data);
unsigned char SPI_Rx();






#endif /* SPIDRIVER_H_ */



