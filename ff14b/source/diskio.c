/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "bsp_spi_flash.h"

/* Definitions of physical drive number for each drive */
#define DEV_SPI_FLASH 0	/* Map SPI_FLASH to physical drive 0 */

#define FLASH_SECTOR_SIZE 512
#define FLASH_BLOCK_SIZE	8
#define FLASH_SECTOR_COUNT 2048*16

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;

	if (pdrv == DEV_SPI_FLASH)
	{
		/* SPI Flash状态检测：读取SPI Flash 设备ID */
		if(sFLASH_ID == SPI_FLASH_ReadID())
		{
			/* 设备ID读取结果正确 */
			stat &= ~STA_NOINIT;
		}
		else
		{
			/* 设备ID读取结果错误 */
			stat = STA_NOINIT;
		}
	}
	return stat;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;
	uint16_t i;

	if (pdrv == DEV_SPI_FLASH)
	{
		/* 初始化SPI Flash */
		SPI_FLASH_Init();

		/* 延时一小段时间 */
		i=500;
		while(--i);	
		/* 唤醒SPI Flash */
		SPI_Flash_WAKEUP();
		/* 获取SPI Flash芯片状态 */
		stat=disk_status(pdrv);
	}
	return stat;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res = RES_PARERR;
	if (pdrv == DEV_SPI_FLASH)
	{
		while(count--)
		{
			SPI_FLASH_BufferRead(buff, sector*FLASH_SECTOR_SIZE, FLASH_SECTOR_SIZE);
			sector++;
			buff+=FLASH_SECTOR_SIZE;
		}
		res = RES_OK;
	}
	return res;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res = RES_PARERR;
	if (pdrv == DEV_SPI_FLASH)
	{
		while(count --)
		{
			SPI_FLASH_SectorErase(sector*FLASH_SECTOR_SIZE);
			SPI_FLASH_BufferWrite((uint8_t *)buff,sector*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);
			sector++;
			buff+=FLASH_SECTOR_SIZE;
		}
		res = RES_OK;
	}

	return res;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res = RES_PARERR;

	if (pdrv == DEV_SPI_FLASH)
	{
		switch (cmd) 
		{
			case CTRL_SYNC:
				break;
			case GET_SECTOR_COUNT:
				*(DWORD * )buff = FLASH_SECTOR_COUNT;	
			break;
			/* 扇区大小  */
			case GET_SECTOR_SIZE :
				*(WORD * )buff = FLASH_SECTOR_SIZE;
			break;
			/* 同时擦除扇区个数 */
			case GET_BLOCK_SIZE :
				*(DWORD * )buff = FLASH_BLOCK_SIZE;
			break;        
      	}
		res = RES_OK;
	}

	return res;
}

__weak DWORD get_fattime(void) {
	/* 返回当前时间戳 */
	return	  ((DWORD)(2015 - 1980) << 25)	/* Year 2015 */
			| ((DWORD)1 << 21)				/* Month 1 */
			| ((DWORD)1 << 16)				/* Mday 1 */
			| ((DWORD)0 << 11)				/* Hour 0 */
			| ((DWORD)0 << 5)				  /* Min 0 */
			| ((DWORD)0 >> 1);				/* Sec 0 */
}
