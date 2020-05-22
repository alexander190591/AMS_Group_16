/*
 * SDCardDriver.c
 *
 * Created: 16-04-2020 13:56:55
 *  Author: Tonni
 */ 


#include <avr/io.h>
#include <ctype.h>
#include <stdio.h>
#include "../include/SDCardDriver.h"
#include "../../defines.h"

#define DUMMYBYTE 0xFF




unsigned char Command(unsigned char cmd, long arg){

	unsigned char retry = 0, status;
	int SDHC_flag = 0; 
	if(SDHC_flag == 0)
	{
		if(cmd == READ_SINGLE_BLOCK      ||
		cmd == READ_MULTIPLE_BLOCKS   ||
		cmd == WRITE_SINGLE_BLOCK     ||
		cmd == WRITE_MULTIPLE_BLOCKS  ||
		cmd == ERASE_BLOCK_START_ADDR ||
		cmd == ERASE_BLOCK_END_ADDR)
		{
			arg = arg << 9;
		}
	}

	
	unsigned char _byte;
	SPI_SlaveSelect(SD_READER_CS, true);
	//SPI_Tx(0xFF);		//	transmitting dummy byte
	SPI_Tx(cmd | 0x40 );	//	sending command token
	

	//	because of endian-ness we want to send MSB first (little endian)
	SPI_Tx((unsigned char)arg >> 24);
	SPI_Tx((unsigned char)arg >> 16);
	SPI_Tx((unsigned char)arg >> 8);
	SPI_Tx((unsigned char)arg);

	if(cmd == SEND_IF_COND)	//it is compulsory to send correct CRC for CMD8 (CRC=0x87) & CMD0 (CRC=0x95)
	SPI_Tx(0x87); //for remaining commands, CRC is ignored in SPI mode
	else
	SPI_Tx(0x95);	//	hardcoded CRC as it is only needed this once

	while((_byte = SPI_Rx()) == 0xff) //wait for response
	{
		if(retry++ > 254)
		break; //time out error
	}

	if(_byte == 0x00 && cmd == READ_OCR) //checking response of CMD58
	{
		status = SPI_Rx() & 0x40; //first byte of the OCR register (bit 31:24)
		if(status == 0x40)
		SDHC_flag = 1; //we need it to verify SDHC card
		else
		SDHC_flag = 0;

		SPI_Rx(); //remaining 3 bytes of the OCR register are ignored here
		SPI_Rx(); //one can use these bytes to check power supply limits of SD
		SPI_Rx();
	}


	
	SPI_Rx(); //extra 8 CLK
	SPI_SlaveSelect(SD_READER_CS, false);
	return _byte; //return state


	//SPI_Tx(0xFF);	//	sending a dummy byte to allow the card time to react

	//return SPI_Rx();		//	return response value from SD
}

int InitSD_Reader(){
	unsigned char i, response, SD_version;
	unsigned int retry = 0;

	SPI_Init('B', SD_READER_OUT, SD_READER_IN, SD_READER_CS, SD_READER_CLK );

	for(i = 0; i < 10; i++)
	{
		SPI_Tx(0xff); //80 clock pulses before sending the first command (Only needs 76, but we just do 80 to be sure)
	}
	
	SPI_SlaveSelect(SD_READER_CS, true);
	do
	{
		response = Command(GO_IDLE_STATE, 0); //send 'reset & go idle' command (= CMD0)
		retry++;
		if(retry > 0x20)
		{
			SendString("\r\n\r\n SD INIT: time out, card not detected \r\n");
			return 0; //time out, card not detected
		}
	} while(response != 0x01); //repeat until SD is in IDLE state

	SPI_SlaveSelect(SD_READER_CS, false);
	SPI_Tx (0xff);
	SPI_Tx (0xff);

	retry = 0;
	
	SD_version = 2; //default set to SD compliance with ver2.x;
	//this may change after checking the next command
	do
	{
		response = Command(SEND_IF_COND, 0x000001AA); //Check power supply status, mandatory for SDHC card (= CMD8)
		retry++;
		if(retry > 0xfe)
		{
			SD_version = 1;
			cardType = 1;
			break;
		} //time out
	} while(response != 0x01);
	
	retry = 0;
	do
	{
		response = Command(APP_CMD, 0); //CMD55, must be sent before sending any ACMD command
		response = Command(SD_SEND_OP_COND, 0); //ACMD41

		retry++;
		if(retry > 0xfe)
		{		
			SendString("\r\n\r\n SD INIT: time out, card initialization failed \r\n");
			return 0;//time out, card initialization failed
		}
		
	} while(response != 0x00);
	
	retry = 0;
	SDHC_flag = 0;
	
	if (SD_version == 2)
	{
		do
		{
			response = Command(READ_OCR, 0); // (=CMD58)
			retry++;
			if(retry > 0xfe)
			{
				cardType = 0;
				break;
			} //time out
		} while(response != 0x00);
		
		if(SDHC_flag == 1)
		cardType = 2;
		else
		cardType = 3;
	}

	Command(CRC_ON_OFF, OFF); //disable CRC; default - CRC disabled in SPI mode
	Command(SET_BLOCK_LEN, 512); //set block size to 512; default size is 512
	
	SendString("\r\n\r\n SD INIT: SD er initialiseret \r\n");
	
	return 1; //successful return

	//	sending reset command: Part1_Physical_Layer_Simplified_Specification_Ver6.00.pdf page 230
// 	_byte = SPI_CycleByte(0x00 | 0x40);
// 	_byte = SPI_CycleByte(0x00);
// 	_byte = SPI_CycleByte(0x00);
// 	_byte = SPI_CycleByte(0x00);
// 	_byte = SPI_CycleByte(0x00);
// 	_byte = SPI_CycleByte(0x95);
// 
// 	SPI_Tx(0x00 | 0x40);
// 	SPI_Tx(0x00);
// 	SPI_Tx(0x00);
// 	SPI_Tx(0x00);
// 	SPI_Tx(0x00);
// 	SPI_Tx(0x95);
// 
// 	//	waiting for SD to enter idle state (returns 0x01)
// 	for (l=0; l<500; l++){
// //		_byte = SPI_CycleByte(0xFF);
// 		_byte = SPI_Rx(0xFF);
// 		//SendString( _byte);
// 		if (_byte == 0x01){
// 		SendString("got a 0x01 now!");
// 		break;
// 		}
// 	}
// 	
// 	
// 	//SendString("did NOT get a 0x01!");
// 	
// 	//	returning error if CMD0 fails
// 	if (!(_byte == 0x01))	{ 
// 	SendString("CMD0 failed ! ");
// 	return 0; } 
// 
// 	for (l=0; l<1000; l++)	{
// 		_byte = Command(APP_CMD, 0);
// 		_byte = Command(SD_SEND_OP_COND,0);
// 		//	break loop if cmd 55 and 41 are OK.
// 		if (!_byte)	{ break; }
// 	}
// 	//	should not happen, but if the data received is 0 at this point, there is something wrong, returning error. 
// 	if ( _byte != 0 )	{ return 0; }
// 
// 	//	Setting block size
// 	_byte = Command(SET_BLOCK_LEN,BLOCKSIZE);
// 
// 	SPI_SlaveSelect(SD_READER_CS, false);
// 	for (l=0; l<3; l++)	{ _byte = SPI_CycleByte(0xFF); }
// 	SPI_SlaveSelect(SD_READER_CS, true);
// 
// 	//	returning 1 if all is ok. 
// 	return 1;
}


unsigned char ReadBlock(unsigned char * buffer, unsigned long startAddress){
	
	int i;
	unsigned char c, r1;

	// checking if the start address is not at the beginning of a block. 
	//if (startAddress % BLOCKSIZE != 0)	{ return 0; }
	SendString("\r\n\r\n ReadBlock: before first command \r\n");
//	r1 = Command(READ_SINGLE_BLOCK, startAddress);
	r1 = Command(READ_SINGLE_BLOCK, startAddress);

	SendString("\r\n\r\n ReadBlock: after first command \r\n");
	//	wait for SD to locate data
	
	if(r1 != 0x00){
	SendString("\r\n\r\n r1 blev = 0x00 \r\n");
	
	
	//return r1; //check for SD status: 0x00 - OK (No flags set)
	return 0;
	}
	SPI_SlaveSelect(SD_READER_CS, true);
	r1 = 0;
	SendString("\r\n\r\n ReadBlock: after Slave CS  \r\n");
	while(SPI_Rx() != 0b11111110) //wait for start single block token (0b11111110)
	{
		
		if(r1++ > 65000)
		{
			SendString("\r\n\r\n ReadBlock: timeout in first loop \r\n");
			SPI_SlaveSelect(SD_READER_CS, false);
			return 0;
		} //return if time-out
	}

	SendString("\r\n\r\n Read Block: \r\n");
	for (i=0;i<BLOCKSIZE;i++)	{
		c = SPI_Rx();
		//SendChar(&c);
		buffer[i]=c;
	}
	SendString("\r\n\r\n Read Block end \r\n");

	SPI_Rx(); //receive incoming CRC (16-bit), CRC is ignored here
	SPI_Rx();
	SPI_Rx(); //extra 8 clock pulses
	SPI_SlaveSelect(SD_READER_CS, false);
	
	SendString("\r\n\r\n ReadBlock: success! \r\n");
	return 1;

// 	for (int i = 0; i<50; i++)	{
// 		//	If return is empty we break out of the loop.
// 		if (r1 == 0x00) break;
// 		r1 = SPI_CycleByte(0xFF);
// 	}
// 	// return error if return data is 0 
// 	if (r1 != 0x00) return 0;
// 
// 
// 	c = SPI_CycleByte(0xFF);
// 	//	waiting for 
// 	while (c != 0xFE)	{ c = SPI_CycleByte(0xFF); }



	//	clearing queues with a few dummy bytes
// 	SPI_CycleByte(0xFF);
// 	SPI_CycleByte(0xFF);
// 	SPI_CycleByte(0xFF);
// 
// 	return 1;
}


unsigned char WriteBlock(unsigned char * data, unsigned long startAddress){
	
	unsigned int retry = 0;
	unsigned char c[1]; 
	short i; 
	// checking if the start address is not at the beginning of a block. 
	if (startAddress % BLOCKSIZE != 0)	
	{
		SendString("\r\n\r\n Write Block: invalid startAddress\r\n");
		return 0; 
	}

	// if write cmd dont return 0 theres an write error. 
	//if (Command(WRITE_SINGLE_BLOCK,startAddress) != 0)	{ return 0; }

	SPI_SlaveSelect(SD_READER_CS, true);
	SPI_Tx(0b11111110); //Send start single block token (0b11111110)
// 		//clearing any data before sending actual data.
// 		SPI_Tx(0xFF);
// 		SPI_Tx(0xFF);
// 		SPI_Tx(0xFF);

	//	
	
	SendString("\r\n\r\n Write Block: \r\n");
	for (i = 0; i < BLOCKSIZE; i++)	{ 
		c[0] = (&data)[i];
		/*SendString(*c);*/
		SendChar(c[0]);
		SPI_Tx(c[0]); 
		data++;
	}
	
	SendString("\r\n\r\n Write Block end \r\n");
	//	Dummies before getting response
	SPI_Tx(0xFF);
	SPI_Tx(0xFF);


	while(SPI_Rx() == 0) //wait for SD card to complete writing and get idle
	{
		if(retry++ > 65000)
		{
			SendString("\r\n\r\n Write Block: Wait for idle failed! \r\n");
			SPI_SlaveSelect(SD_READER_CS, false);
			return 0;
		}

	}

	SPI_SlaveSelect(SD_READER_CS, false);
	SPI_Tx(0xff);   //just spend 8 clock cycle delay before reasserting the CS line
	SPI_SlaveSelect(SD_READER_CS, true);    //re-asserting the CS line to verify if card is still busy

	while(SPI_Rx() == 0) //wait for SD card to complete writing and get idle
	{
		if(retry++ > 65000)
		{
			SendString("\r\n\r\n Write Block: failed to complete write \r\n");

			SPI_SlaveSelect(SD_READER_CS, false);
			return 0;
		}
	}
	
	SendString("\r\n\r\n Write Block: write complete \r\n");
	SPI_SlaveSelect(SD_READER_CS, false);
	return 1;


	//SPI_Rx(0xFF);
	//c &= 0x1F;	//	Mask for Write error - see documentation for SD
	
	
	
	//while (SPI_CycleByte(0xFF) != 0xFF) { }	// waiting until buffer is empty. 
	
	//return 1;


}







//	burde være med et variabelt antal argumenter, men grundet tidspres er den hardcoded til de tre vi skal bruge
void CollectData(SensorDataObj * dataObj, double tempAir, double humidityAir, double humiditySoil)
{
	//	we want to save three doubles (= 24 bytes) - just to make sure we have space enough in a slot, ill make rook for 4 doubles, and double that up to 64 bytes.

	dataObj->tempAir		= tempAir;
	dataObj->humidityAir	= humidityAir;
	dataObj->humiditySoil	= humiditySoil;
	
}





/*
unsigned char WriteSaveSlot(int saveSlot) {

	//	slot 0 = 0 + blockSize

	//cant save in slot 0
	if (saveSlot <= 0)
	{
		return 0;

	}

	int pos = 0;

	unsigned char inData;

	for (size_t i = 0; i < sizeof(int); ++i)
	{
		inData = *((unsigned char *)& saveSlot + i);
		WriteBlock(&inData, i);
	}

	//returns success
	return 1;
}*/

unsigned char WriteRawData(SensorDataObj * dataObj, int saveSlot) {

	//	slot 0 = 0 + blockSize

	//cant save in slot 0
	if (saveSlot <= 0)
	{
		SendString("\r\n\r\n WriteRawData: saveSlot cannot be 0 or less\r\n");
		return 0;

	}

	int pos = 0;
	unsigned char * inData = (unsigned char*)&dataObj;
	SendString("\r\n\r\n In WriteRawData -  Print inData before Read: \r\n");
	SendString(inData);
	unsigned char buffer[BLOCKSIZE];
	for (size_t i = 0; i < sizeof(SensorDataObj); ++i)
	{
		buffer[i] = inData[i];
	}
	SendString("\r\n\r\n In WriteRawData - Print buffer data before Read: \r\n");
	SendString(&buffer);
	WriteBlock(&buffer, (saveSlot * BLOCKSIZE));

	//WriteSaveSlot(saveSlot);


	//returns success
	SendString("\r\n\r\n WriteRawData: success!\r\n");
	return 1;

}


/*
int ReadSavePosition() {

	int saveSlot;
	unsigned char * buffer = NULL;



	for (int i = 0; i<sizeof(int); i++)
	{
		ReadBlock(buffer, i);
		saveSlot = ((int)buffer) << (i * 8);

	}


	return saveSlot;
}
*/

SensorDataObj * ReadRawData(int saveSlot) {

	unsigned char outData[sizeof(SensorDataObj)];

	unsigned char buffer[BLOCKSIZE];
	SendString("\r\n\r\n ReadRawData: Start \r\n");

	ReadBlock(&buffer, (saveSlot * BLOCKSIZE));
	SendString("\r\n\r\n ReadRawData: buffer after read: \r\n");
	SendString(&buffer);

	for (size_t i = 0; i<sizeof(SensorDataObj); i++)
	{
		outData[i] = buffer[i];
	}
	
	SendString("\r\n\r\n ReadRawData: Saved data after Read: \r\n");
	SendString(&outData);

	
	SendString("\r\n\r\n ReadRawData: success!\r\n");
	return ((SensorDataObj *)outData);
}
