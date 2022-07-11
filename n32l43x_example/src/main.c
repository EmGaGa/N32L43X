#include "header.h"

dev_handler_str dev_handler_s;

static void MainInit(void);

static struct rt_thread main_thread;
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t rt_main_thread_stack[1024];
static void main_thread_entry(void * para);
static rt_uint8_t main_thread_priority = 6;

static void MainInit(void)
{
    /* LED Init */
    LedInit();

    /* KEY Init */
    KeyInit();

    /* 按键注册 */
    KeyRegister();

    /* LCD Init */
    LCD240x240_Init();

    /* backlight on */
    LCD_BackLight(true);
}

/**
 * @brief  Main program
 */
int main(void)
{
    PRO_LOG(LOG_DEBUG, "entry %s. \r\n", __func__);
    MainInit();
    /* main thread */
	rt_thread_init(&main_thread,
					"main_thread",
					main_thread_entry,
					RT_NULL,
					&rt_main_thread_stack,
					sizeof(rt_main_thread_stack),
					main_thread_priority,
					1000);
	rt_thread_startup(&main_thread);
}

static void main_thread_entry(void * para)
{
    PRO_LOG(LOG_DEBUG, "Entry %s. \r\n", __func__);
//    LCD_Fill(0,0, LCD_W,LCD_H,RED);
//    rt_thread_delay(1000);
//    LCD_Fill(0,0, LCD_W,LCD_H,GREEN);
//    rt_thread_delay(1000);
//    LCD_Fill(0,0, LCD_W,LCD_H,BLUE);
    while(1)
    {
        rt_thread_delay(1000);
    }
}

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE* f)
{
    USART_SendData(USARTx, (uint8_t)ch);
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXDE) == RESET)
        ;

    return (ch);
}

#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param file pointer to the source file name
 * @param line assert_param error line source number
 */
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}

#endif
