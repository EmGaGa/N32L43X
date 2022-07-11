#include "lcd_init.h"
#include "rtthread.h"

void LCD_SPI_Write(uint8_t Data)
{
    /* Send data */
	SPI_I2S_TransmitData(SPI_PERIPH, Data);
    
	/* Wait tx buffer empty */
	while (SPI_I2S_GetStatus(SPI_PERIPH, SPI_I2S_TE_FLAG) == RESET);
}

void LCD_SPI_Init(void)
{
    SPI_InitType SPI_InitStructure;

    /*!< SPI configuration */
    SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_TX;
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;
    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_HIGH;
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;

    SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_2;

    SPI_InitStructure.FirstBit = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly  = 7;
    SPI_Init(SPI_PERIPH, &SPI_InitStructure);

    /*!< Enable the SPI_PERIPH  */
    SPI_Enable(SPI_PERIPH, ENABLE);
}

void LCD_GPIO_Init(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Enable the GPIO Clock */
	RCC_EnableAPB2PeriphClk(SPI_RCC_PERIPH|SPI_SCK_RCC_PERIPH|RCC_APB2_PERIPH_AFIO, ENABLE);
    /*!< SPI2 Periph clock enable */
    RCC_EnableAPB2PeriphClk(SPI_LCD_CLK, ENABLE);

    /* Configure the GPIO pin */
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin        = RES_PIN | BLK_PIN;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(RES_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = DC_PIN;
	GPIO_InitPeripheral(DC_PORT, &GPIO_InitStructure);

	/*!< Configure SPI2 pins: SCK */
    GPIO_InitStructure.Pin        = SPI_SCK_PIN;
	GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_SPI2;
    GPIO_InitPeripheral(SPI_SCK_PORT, &GPIO_InitStructure);

    /*!< Configure SPI2 pins: MOSI */
    GPIO_InitStructure.Pin = SPI_MOSI_PIN;
    GPIO_InitPeripheral(SPI_MOSI_PORT, &GPIO_InitStructure);
}

/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(uint8_t dat) 
{	
	LCD_SPI_Write(dat);
}

/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(uint8_t dat)
{
	LCD_DC_Set();
	LCD_SPI_Write(dat);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(uint16_t dat)
{
	LCD_DC_Set();
	LCD_SPI_Write(dat>>8);
	LCD_SPI_Write(dat);
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(uint8_t dat)
{
	LCD_DC_Clr();
	LCD_SPI_Write(dat);
}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	LCD_WR_REG(0x2a);     //Column address set
	LCD_WR_DATA(x1);    //start column
	LCD_WR_DATA(x2);    //end column

	LCD_WR_REG(0x2b);     //Row address set
	LCD_WR_DATA(y1);    //start row
	LCD_WR_DATA(y2);    //end row
	LCD_WR_REG(0x2C);     //Memory write
}

void LCD240x240_Init(void)
{
	LCD_GPIO_Init();//初始化GPIO
	LCD_SPI_Init();
	LCD_RES_Clr();
//	delay_1ms(120);
	rt_thread_delay(120);
	LCD_RES_Set();
//	delay_1ms(120);
	rt_thread_delay(120);
//	LCD_SCLK_Set();			//特别注意！！
    LCD_WR_REG(0x11); 			//Sleep Out
//	delay_1ms(120);               //DELAY120ms 
	rt_thread_delay(120);
	//-----------------------ST7789V Frame rate setting-----------------//
	//************************************************
	LCD_WR_REG(0x3A);        //65k mode
	LCD_WR_DATA8(0x05);

	LCD_WR_REG(0xC5); 		//VCOM
	LCD_WR_DATA8(0x1A);
	LCD_WR_REG(0x36);                 // 屏幕显示方向设置
	LCD_WR_DATA8(0x00);
	//-------------ST7789V Frame rate setting-----------//
	LCD_WR_REG(0xb2);		//Porch Setting
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x33);

	LCD_WR_REG(0xb7);			//Gate Control
	LCD_WR_DATA8(0x05);			//12.2v   -10.43v
	//--------------ST7789V Power setting---------------//
	LCD_WR_REG(0xBB);//VCOM
	LCD_WR_DATA8(0x3F);

	LCD_WR_REG(0xC0); //Power control
	LCD_WR_DATA8(0x2c);

	LCD_WR_REG(0xC2);		//VDV and VRH Command Enable
	LCD_WR_DATA8(0x01);

	LCD_WR_REG(0xC3);			//VRH Set
	LCD_WR_DATA8(0x0F);		//4.3+( vcom+vcom offset+vdv)

	LCD_WR_REG(0xC4);			//VDV Set
	LCD_WR_DATA8(0x20);				//0v

	LCD_WR_REG(0xC6);				//Frame Rate Control in Normal Mode
	LCD_WR_DATA8(0X01);			//111Hz

	LCD_WR_REG(0xd0);				//Power Control 1
	LCD_WR_DATA8(0xa4);
	LCD_WR_DATA8(0xa1);

	LCD_WR_REG(0xE8);				//Power Control 1
	LCD_WR_DATA8(0x03);

	LCD_WR_REG(0xE9);				//Equalize time control
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x08);
	//---------------ST7789V gamma setting-------------//
	LCD_WR_REG(0xE0); //Set Gamma
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x14);
	LCD_WR_DATA8(0x28);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x14);
	LCD_WR_DATA8(0x28);
	LCD_WR_DATA8(0x30);
		
	LCD_WR_REG(0XE1); //Set Gamma
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x03);
	LCD_WR_DATA8(0x24);
	LCD_WR_DATA8(0x32);
	LCD_WR_DATA8(0x32);
	LCD_WR_DATA8(0x3B);
	LCD_WR_DATA8(0x14);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x28);
	LCD_WR_DATA8(0x2F);

	LCD_WR_REG(0x21); 		//反显
	
	LCD_WR_REG(0x29);         //开启显示 
} 
