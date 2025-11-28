/*-----------------------------------------------------------------------*/
/* Low level disk I/O module for FatFs (RP2040 Flash)                    */
/*-----------------------------------------------------------------------*/

#include "ff.h"
#include "diskio.h"
#include "../msc_disk.h"  // Include our flash helpers

// We define Drive 0 as our Internal Flash
#define DEV_FLASH 0

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/
DSTATUS disk_status (BYTE pdrv)
{
    if (pdrv != DEV_FLASH) return STA_NOINIT;
    return 0; // Always ready
}

/*-----------------------------------------------------------------------*/
/* Initialize a Drive                                                    */
/*-----------------------------------------------------------------------*/
DSTATUS disk_initialize (BYTE pdrv)
{
    if (pdrv != DEV_FLASH) return STA_NOINIT;
    return 0; // Always initialized
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/
DRESULT disk_read (BYTE pdrv, BYTE *buff, LBA_t sector, UINT count)
{
    if (pdrv != DEV_FLASH) return RES_PARERR;
    
    for (UINT i = 0; i < count; i++) {
        // Call the helper defined in msc_disk.c
        flash_read_512(sector + i, buff + (i * BLOCK_SIZE));
    }
    
    return RES_OK;
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/
DRESULT disk_write (BYTE pdrv, const BYTE *buff, LBA_t sector, UINT count)
{
    if (pdrv != DEV_FLASH) return RES_PARERR;
    
    for (UINT i = 0; i < count; i++) {
        // Call the helper defined in msc_disk.c
        flash_write_512(sector + i, buff + (i * BLOCK_SIZE));
    }
    
    return RES_OK;
}

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/
DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void *buff)
{
    if (pdrv != DEV_FLASH) return RES_PARERR;
    
    switch (cmd) {
        case CTRL_SYNC: 
            return RES_OK;
            
        case GET_SECTOR_COUNT: 
            *(DWORD*)buff = SECTOR_COUNT; 
            return RES_OK;
            
        case GET_SECTOR_SIZE: 
            *(WORD*)buff = BLOCK_SIZE; 
            return RES_OK;
            
        case GET_BLOCK_SIZE: 
            *(DWORD*)buff = 1; // Erase block size in units of sectors
            return RES_OK;
    }
    
    return RES_PARERR;
}