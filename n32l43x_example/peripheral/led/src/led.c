#include "header.h"

static void LedOn(GPIO_Module* GPIOx, uint16_t Pin);
static void LedOff(GPIO_Module* GPIOx, uint16_t Pin);
//static void LedOnOff(GPIO_Module* GPIOx, uint32_t Pin);
static void LedBlink(GPIO_Module* GPIOx, uint16_t Pin);

/**
 * @brief  Turns selected Led on as output low level.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
static void LedOn(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBSC = Pin;
}
/**
 * @brief  Turns selected Led Off as output high level.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
static void LedOff(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBC = Pin;
}
#if 0
/**
 * @brief  Turns selected Led on or off.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be one of the following values:
 *  @arg GPIO_PIN_0~GPIO_PIN_15: set related pin on
 *      @arg (GPIO_PIN_0<<16)~(GPIO_PIN_15<<16): clear related pin off
 */
static void LedOnOff(GPIO_Module* GPIOx, uint32_t Pin)
{
    GPIOx->PBSC = Pin;
}
#endif
/**
 * @brief  Toggles the selected Led.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
static void LedBlink(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->POD ^= Pin;
}

void LedInit(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Enable the GPIO Clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    
    /* Configure the GPIO pin */
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin        = LED1_PIN;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(LED_PORT_GROUP1, &GPIO_InitStructure);

    GPIO_InitStructure.Pin        = LED2_PIN;
    GPIO_InitPeripheral(LED_PORT_GROUP2, &GPIO_InitStructure);

    GPIO_InitStructure.Pin        = LED3_PIN;
    GPIO_InitPeripheral(LED_PORT_GROUP2, &GPIO_InitStructure);
}

void LedCtrl(uint8_t index, uint8_t sta)
{
    if(index == 0)
    {
        if(sta)
        {
            LedOn(LED_PORT_GROUP1, LED1_PIN);
        }
        else
        {
            LedOff(LED_PORT_GROUP1, LED1_PIN);
        }
    }
    else if(index == 1)
    {
        if(sta)
        {
            LedOn(LED_PORT_GROUP2, LED2_PIN);
        }
        else
        {
            LedOff(LED_PORT_GROUP2, LED2_PIN);
        }
    }
    else if(index == 2)
    {
        if(sta)
        {
            LedOn(LED_PORT_GROUP2, LED3_PIN);
        }
        else
        {
            LedOff(LED_PORT_GROUP2, LED3_PIN);
        }
    }
}

void LedToggle(uint8_t index)
{
    if(index == 0)
    {
        LedBlink(LED_PORT_GROUP1, LED1_PIN);
    }
    else if(index == 1)
    {
        LedBlink(LED_PORT_GROUP2, LED2_PIN);
    }
    else if(index == 2)
    {
        LedBlink(LED_PORT_GROUP2, LED3_PIN);
    }
}
