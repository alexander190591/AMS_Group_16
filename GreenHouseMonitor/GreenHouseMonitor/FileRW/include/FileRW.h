/*! \brief Driver for file IO
 *	
 *	Filename:	./GreenHouseMonitor/FileRW/include/FileRW.h
 *	Created:	Created: 07-05-2020 12:11:04
 *	Author:		Tonni Lutze
 *
 *	
 */



#ifndef FILERW_H_
#define FILERW_H_

#pragma once
#include "../../FATDriver/include/FATDriver.h"

#define SEEK_START 0
#define SEEK_END 1

typedef struct
{
	dir_entry_t dir_entry;
	dword position;
	word cluster;   /* Current cluster number */
} file_descriptor_t;

byte file_open(char* filename, file_descriptor_t* fd, byte start_pos);
word file_read(file_descriptor_t *fd, char *buf, word length);
word file_write(file_descriptor_t* fd, char* write_str, word length);
byte file_seek(file_descriptor_t *fd, byte to);
byte file_seek_to_offset(file_descriptor_t *fd, dword offset);
byte init_FAT_fs(void);
byte file_delete(file_descriptor_t* fd);



#endif /* FILERW_H_ */