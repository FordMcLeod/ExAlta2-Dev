/*
 * Copyright (C) 2015  Brandon Borden, Stefan Damkjar, Taeho Kang, and Peng Zhang
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


/**
 * @file fatfs.c
 * @author Stefan Damkjar
 * @date 2015-08-26
 */

#include "fatfs.h"
#include "diskio.h"
#include "microsd.h"
#include "stdio.h"
#include "ff.h"
#include "print.h"

char    ramBufferWrite[FSBUFFERSIZE];  /* Temporary buffer for write file */
char    ramBufferRead[FSBUFFERSIZE];   /* Temporary buffer for read file */


/***************************************************************************//**
 * @brief
 *   This function is required by the FAT file system in order to provide
 *   timestamps for created files. Since this example does not include a
 *   reliable clock we hardcode a value here.
 *
 *   Refer to drivers/fatfs/doc/en/fattime.html for the format of this DWORD.
 * @return
 *    A DWORD containing the current time and date as a packed datastructure.
 ******************************************************************************/
DWORD get_fattime(void)
{
  return (28 << 25) | (2 << 21) | (1 << 16);
}

BYTE FATFS_Init(void)
{

	DSTATUS resCard;              /* SDcard status */
	FRESULT res;                  /* FatFs function common result code */

	resCard = disk_initialize(0); /*Check micro-SD card status */

	switch(resCard)
	{
    case STA_NOINIT:                    /* Drive not initialized */
      return STA_NOINIT;
      break;
    case STA_NODISK:                    /* No medium in the drive */
      return STA_NODISK;
      break;
    case STA_PROTECT:                   /* Write protected */
      return STA_PROTECT;
      break;
    default:
      break;
	}

	/* Initialize filesystem */
	res = f_mount(0, &Fatfs);
	if (res != FR_OK)
	{
	  /* Error.No micro-SD with FAT32 is present */
		return STA_NOFAT32;
	}

	return STA_OK;

}

/* [OUT] File object to create */
/* [IN]  File name to be opened */
BYTE FATFS_append (FIL* fp, const char* path)
{

  BYTE res;

  /* Opens an existing file. If not exist, creates a new file. */
  res = f_open(fp, path, FA_WRITE | FA_OPEN_ALWAYS);
  if (res == FR_OK) {
    /* Seek to end of the file to append data */
    res = f_lseek(fp, f_size(fp));
    if (res != FR_OK)
    {
      f_close(fp);
    }
  }
  return res;
}

BYTE FATFS_Write(char* stringBuffer, char* fileName)
{

  FRESULT res;                  /* FatFs function common result code */
  int     filecounter;

  /*Initialization file buffer write */
  filecounter = snprintf(ramBufferWrite,FSBUFFERSIZE,"%s",stringBuffer);
  if ( filecounter > FSBUFFERSIZE )
  {
	  /* Error. String over-ran the buffer */
	  return FR_INVALID_NAME;
  }

  /* Open  the file for write */
  res = f_open(&fsrc, fileName,  FA_WRITE);
  if (res != FR_OK)
  {
	/*  If file does not exist create it*/
	res = f_open(&fsrc, fileName, FA_CREATE_ALWAYS | FA_WRITE );
	if (res != FR_OK)
	{
	  /* Error. Cannot create the file */
	  return res;
	}
  }

  /*Set the file write pointer to first location */
  res = f_lseek(&fsrc, 0);
  if (res != FR_OK)
  {
	/* Error. Cannot set the file write pointer */
	return res;
  }

  /*Write a buffer to file*/
  res = f_write(&fsrc, ramBufferWrite, filecounter, &bw);
  if ((res != FR_OK) || (filecounter != bw))
  {
	/* Error. Cannot write the file */
	return res;
  }

  /* Close the file */
  f_close(&fsrc);
  if (res != FR_OK)
  {
	/* Error. Cannot close the file */
	return res;
  }

  return FR_OK;
}

BYTE FATFS_Read(char* fileName, uint16_t size)
{

  FRESULT res;                  /* FatFs function common result code */

  /* Open the file for read */
  res = f_open(&fsrc, fileName,  FA_READ);
  if (res != FR_OK)
  {
	/* Error. Cannot create the file */
	return res;
  }

  /*Set the file read pointer to first location */
  res = f_lseek(&fsrc, 0);
  if (res != FR_OK)
  {
	/* Error. Cannot set the file pointer */
	return res;
  }

  /* Read some data from file */
  res = f_read(&fsrc, ramBufferRead, size, &br);
  if ((res != FR_OK) || (size != br))
  {
	/* Error. Cannot read the file */
	return res;
  }

  /* Close the file */
  f_close(&fsrc);
  if (res != FR_OK)
  {
	/* Error. Cannot close the file */
	return res;
  }

  return FR_OK;
}
