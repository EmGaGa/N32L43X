#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "n32l43x.h"

#define LCD_W 240
#define LCD_H 240

#define SPI_SCK_RCC_PERIPH      (RCC_APB2_PERIPH_GPIOC)
#define SPI_RCC_PERIPH          (RCC_APB2_PERIPH_GPIOB)//RCC_APB2_PERIPH_GPIOA

/* RES Port/Pin definition */
#define RES_PORT                (GPIOB)
#define RES_PIN                 (GPIO_PIN_14)
/* DC Port/Pin definition */
#define DC_PORT                 (GPIOC)
#define DC_PIN                  (GPIO_PIN_7)
/* BLK Port/Pin definition */
#define BLK_PORT                (GPIOB)
#define BLK_PIN                 (GPIO_PIN_12)

#define LCD_RES_Clr()           RES_PORT->PBC = RES_PIN         //RES
#define LCD_RES_Set()           RES_PORT->PBSC = RES_PIN

#define LCD_DC_Clr()            DC_PORT->PBC = DC_PIN           //DC
#define LCD_DC_Set()            DC_PORT->PBSC = DC_PIN

#define LCD_BLK_Clr()           BLK_PORT->PBC = BLK_PIN         //BLK
#define LCD_BLK_Set()           BLK_PORT->PBSC = BLK_PIN

#define SPI_PERIPH              (SPI2)
#define SPI_LCD_CLK             (RCC_APB2_PERIPH_SPI2)

/* Define port and pin for SDA and SCL */
#define SPI_SCK_PORT            (GPIOB)
#define SPI_SCK_PIN             (GPIO_PIN_13)

#define SPI_MOSI_PORT           (GPIOB)
#define SPI_MOSI_PIN            (GPIO_PIN_15)


void LCD_SPI_Init(void); //初始化SPI
void LCD_GPIO_Init(void);//初始化GPIO
void LCD_Writ_Bus(uint8_t dat);//模拟SPI时序
void LCD_WR_DATA8(uint8_t dat);//写入一个字节
void LCD_WR_DATA(uint16_t dat);//写入两个字节
void LCD_WR_REG(uint8_t dat);//写入一个指令
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//设置坐标函数
void LCD240x240_Init(void);//LCD初始化

#endif
