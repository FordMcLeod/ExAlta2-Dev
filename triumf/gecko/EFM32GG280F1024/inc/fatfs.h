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
 * @file fatfs.h
 * @author Stefan Damkjar
 * @date 2015-08-26
 */

#ifndef  FATFS_H_
#define  FATFS_H_

#include "ff.h"

#define  FSBUFFERSIZE      (100)

// FIL      fsrc;             /* File objects */
// FATFS    Fatfs;            /* File system specific */
// uint16_t br, bw;           /* File read/write count */

BYTE     FATFS_Init(void);
BYTE 	 FATFS_append (FIL* fp, const char* path);
BYTE     FATFS_Write(char* stringBuffer, char* fileName);
BYTE     FATFS_Read(char* fileName, uint16_t size);

#endif /* FATFS_H_ */
