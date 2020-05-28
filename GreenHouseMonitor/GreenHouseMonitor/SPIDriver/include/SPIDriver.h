 /*! \brief Low level driver for SPI.
 *			
 *			
 *
 *	
 *	
 *	Filename:	./GreenHouseMonitor/SPIDriver/include/SPIDriver.h
 *	Created:	16-04-2020 08:32:41
 *	Author:		Tonni Lutze
 *
 *	Major change #1:
 */



#ifndef SPIDRIVER_H_
#define SPIDRIVER_H_
#pragma once

#include <string.h>
#include <avr/io.h>
#include <stdbool.h>

/**
  * @brief Initiates the SPI Driver.
  * 
  * 
  * @param char port	- The PORT which is to be used. Accepted values are: a - h 
  * @param int misoPin	- The pin which is to be used. Accepted values are defined Arduino GPIO pins (eg. PB1)
  * @param int mosiPin	- The pin which is to be used. Accepted values are defined Arduino GPIO pins (eg. PB1)
  * @param int ssPin	- The pin which is to be used. Accepted values are defined Arduino GPIO pins (eg. PB1)
  * @param int clkPin	- The pin which is to be used. Accepted values are defined Arduino GPIO pins (eg. PB1)
  * 
  * @return void
  * 
**/
void SPI_Init(char port, int misoPin, int mosiPin, int ssPin, int clkPin ); 


/**
  * @brief asserts og de-asserts the SSPin.
  * 
  * 
  * @param int ssPin	- The pin which is to be used. Accepted values are defined Arduino GPIO pins (eg. PB1)
  * @param bool enable	- Boolean value enable or disable (assert or de-assert)
  * 
  * @return void
  * 
**/
void SPI_SlaveSelect(int ssPin, bool enable);


/**
  * @brief Transmits one char via SPI
  * 
  * 
  * @param unsigned char data	- The data to be sent.
  * 
  * @return void
  * 
**/
void SPI_Tx(unsigned char data);


/**
  * @brief Receives one char via SPI
  * 
  * 
  * @param None.
  * 
  * @return unsigned char	- The data that was recieved. 
  * 
**/
unsigned char SPI_Rx();


/**
  * @brief Transmits and Receives one char via SPI
  *
  *	This is basicly a combinatio of SPI_Tx() and SPI_Rx()
  * 
  * 
  * @param unsigned char	- The data to be sent.
  * 
  * @return unsigned char	- The data that was recieved. 
  * 
**/
unsigned char SPI_CycleByte(unsigned char inData);

#endif /* SPIDRIVER_H_ */