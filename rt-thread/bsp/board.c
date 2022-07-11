/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-07-24     Tanek        the first version
 * 2018-11-12     Ernest Chen  modify copyright
 */
 
#include <stdint.h>
#include <rtthread.h>
#include "header.h"


static void sysTick_Init(void);
static void SysClkConfig(void);

static void SysClkConfig(void)
{
    RccInit();
}

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
#define RT_HEAP_SIZE 4096
static uint32_t rt_heap[RT_HEAP_SIZE];     // heap default size: 4K(1024 * 4)
RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

/**
 * This function will initial your board.
 */
void rt_hw_board_init()
{
    /* Call components board initial (use INIT_BOARD_EXPORT()) */
	SysClkConfig();
	sysTick_Init();

    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif


#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif

    /* shell usart init */
    Usart_Init();
}

void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

static void sysTick_Init(void)
{
    RCC_ClocksType RCC_ClockFreq;
    
    RCC_GetClocksFreqValue(&RCC_ClockFreq);

    SysTick_Config(RCC_ClockFreq.SysclkFreq/RT_TICK_PER_SECOND);
}

void rt_hw_console_output(const char *str)
{
	rt_size_t i = 0, size = 0;
	char a = '\r';

	size = rt_strlen(str);
	for (i = 0; i < size; i++)
	{
		if (*(str + i) == '\n')
		{
            USART_SendData(USARTx, a);
            while (RESET == USART_GetFlagStatus(USARTx, USART_FLAG_TXC))
		    {
		        ;
		    }
		}

        USART_SendData(USARTx, *(str + i));
        while (RESET == USART_GetFlagStatus(USARTx, USART_FLAG_TXC))
        {
            ;
        }
	}
}

char rt_hw_console_getchar(void)
{
    int ch = -1;

    if (SET == USART_GetFlagStatus(USARTx, USART_FLAG_RXDNE))
    {
        ch = USART_ReceiveData(USARTx);
    }
    else 
    {
        if(SET == USART_GetFlagStatus(USARTx, USART_FLAG_OREF))
        {
            USART_ClrFlag(USARTx, USART_FLAG_OREF);
        }
        rt_thread_mdelay(10);
    }

    return ch;
}
