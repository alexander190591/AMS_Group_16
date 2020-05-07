/*
 * Test_SPIDriver.c
 *
 * Created: 16-04-2020 13:16:18
 *  Author: Tonni
 */ 


#include <avr/io.h>


#include "../../defines.h"
#include "Test_SPIDriver.h"
#include "../include/SPIDriver.h"


void TestSPIDriver()
{

	SPI_Init('B', SD_READER_OUT, SD_READER_IN, SD_READER_CS, SD_READER_CLK );


}


/*
SD_READER_OUT
SD_READER_IN
SD_READER_CLK
SD_READER_CS
*/