#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#include "n32l43x.h"
#include <stdio.h>

//#define  sFLASH_ID              0xEF3015   //W25X16
//#define  sFLASH_ID              0xEF4015	 //W25Q16
#define  sFLASH_ID              0XEF4018   //W25Q128
//#define  sFLASH_ID              0XEF4017    //W25Q64

#define SPI_FLASH_PageSize              256
#define SPI_FLASH_PerWritePageSize      256

/*命令定义-开头*******************************/
#define W25X_WriteEnable		    0x06 
#define W25X_WriteDisable		    0x04 
#define W25X_ReadStatusReg          0x05 
#define W25X_WriteStatusReg		    0x01 
#define W25X_ReadData			    0x03 
#define W25X_FastReadData		    0x0B 
#define W25X_FastReadDual		    0x3B 
#define W25X_PageProgram		    0x02 
#define W25X_BlockErase			    0xD8 
#define W25X_SectorErase		    0x20 
#define W25X_ChipErase			    0xC7 
#define W25X_PowerDown			    0xB9 
#define W25X_ReleasePowerDown	    0xAB 
#define W25X_DeviceID			    0xAB 
#define W25X_ManufactDeviceID   	0x90 
#define W25X_JedecDeviceID		    0x9F

/* WIP(busy)标志，FLASH内部正在写入 */
#define WIP_Flag                    0x01
#define Dummy_Byte                  0xFF
/*命令定义-结尾*******************************/

#define     SPI_FLASH_PERIPH                    SPI1
#define     SPI_FLASH_RCC_PERIPH                RCC_APB2_PERIPH_SPI1
#define     SPI_FLASH_GPIO_PERIPH               RCC_APB2_PERIPH_GPIOA

//SCK引脚
#define     SPI_FLASH_SCK_PORT                  GPIOA
#define     SPI_FLASH_SCK_PIN                   GPIO_PIN_5
//MOSI引脚
#define     SPI_FLASH_MOSI_PORT                 GPIOA
#define     SPI_FLASH_MOSI_PIN                  GPIO_PIN_7
//MISO引脚
#define     SPI_FLASH_MISO_PORT                 GPIOA
#define     SPI_FLASH_MISO_PIN                  GPIO_PIN_6
//CS(NSS)引脚 片选选普通GPIO即可
#define     SPI_FLASH_CS_PORT                   GPIOA
#define     SPI_FLASH_CS_PIN                    GPIO_PIN_4

#define     SPI_FLASH_CS_LOW()     		        SPI_FLASH_CS_PORT->PBC = SPI_FLASH_CS_PIN 
#define     SPI_FLASH_CS_HIGH()    			    SPI_FLASH_CS_PORT->PBSC = SPI_FLASH_CS_PIN

/*SPI接口定义-结尾****************************/

/*等待超时时间*/
#define SPIT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT         ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))

/*信息输出*/
#define FLASH_DEBUG_ON         1

#define FLASH_INFO(fmt,arg...)          printf("<<-FLASH-INFO->> "fmt"\n",##arg)
#define FLASH_ERROR(fmt,arg...)         printf("<<-FLASH-ERROR->> "fmt"\n",##arg)
#define FLASH_DEBUG(fmt,arg...)         do{\
                                            if(FLASH_DEBUG_ON)\
                                            printf("<<-FLASH-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                        }while(0)

void SPI_FLASH_Init(void);
void SPI_FLASH_SectorErase(uint32_t SectorAddr);
void SPI_FLASH_BulkErase(void);
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint32_t SPI_FLASH_ReadID(void);
uint32_t SPI_FLASH_ReadDeviceID(void);
void SPI_FLASH_StartReadSequence(uint32_t ReadAddr);
void SPI_Flash_PowerDown(void);
void SPI_Flash_WAKEUP(void);


uint8_t SPI_FLASH_ReadByte(void);
uint8_t SPI_FLASH_SendByte(uint8_t byte);
uint16_t SPI_FLASH_SendHalfWord(uint16_t HalfWord);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WaitForWriteEnd(void);


#endif /* __SPI_FLASH_H */

