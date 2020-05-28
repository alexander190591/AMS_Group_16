/*! \brief Driver for FAT file system
 *	
 *			Description here
 *
 *
 *	
 *	Filename:	./GreenHouseMonitor/FATDriver/include/FATDriver.h
 *	Created:	Created: 07-05-2020 11:09:56
 *	Author:		Tonni Lutze
 *
 *	
 */


#ifndef FATDRIVER_H_
#define FATDRIVER_H_

#pragma once
#include "../../SDCardDriver/include/SDCardDriver.h"
#include <string.h>	
#include "../../defines.h"
#include <ctype.h>

#define PARTENTRY1 0x1be  // offset of 1st partition entry
#define NEW_FILE_ATTR 0x20  // only set the archive bit when creating a new file

void memreverse(void* from, void* to, size_t length);
char* str_toupper(char *str);
char* str_n_toupper(char *str, word n);
void delay(void);

// partition info
typedef struct
{
	word bytes_per_sec;  //bytes per sector
	word FAT_size;
	dword FAT_addr;  //FAT address
	word clus_size; //size of a cluster in bytes
	word root_dir_size;   /* size of root directory */
	dword root_dir_addr;  //root dir address
	dword data_addr;  // address of start of data blocks
} partition_info_t;

extern partition_info_t prtn;
extern byte g_block_buf[512];

typedef struct
{
	char filename[12];  /** The file's name and extension, total 11 chars padded with spaces. */
	byte attributes;  /** The file's attributes. Mask of the FAT_ATTRIB_* constants. */
	byte unused_attr[14]; /** Attributes in direntry which are unused or unsupported */
	word first_cluster;     /** The cluster in which the file's first byte resides. */
	dword filesize;   /** The file's size. */
	dword entry_addr; /** The total disk offset of this directory entry. */
} dir_entry_t;

dword get_sec_addr(word cluster, dword position);
word next_clus(word clus, byte *buf);
byte initFAT(byte* buf);
word get_unused_cluster(byte* buf);
dword get_empty_dir_entry(byte* buf);
byte create_dir_entry(dir_entry_t* de, char* filename, byte fn_length, byte* buf);
byte write_dir_entry(dir_entry_t* de, byte* buf);
byte invalidate_dir_entry(dir_entry_t* de, byte* buf);
word clear_FAT(byte* buf, word cluster);
byte update_FAT(byte* buf, word cluster, word value);
void prtn_set_addr(byte* bootSec, dword partition_addr);
byte getFile(dir_entry_t* de, byte* buf, char* filename, byte length);
byte create_file(dir_entry_t* de, char* filename, byte fn_length, byte* buf);

#endif /* FATDRIVER_H_ */