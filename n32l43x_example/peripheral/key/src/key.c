#include "header.h"

extern dev_handler_str dev_handler_s;

static void BtnUp_Single_Clicked_Handler(void* btn);
static void BtnDown_Single_Clicked_Handler(void* btn);
static void BtnLeft_Single_Clicked_Handler(void* btn);
static void BtnRight_Single_Clicked_Handler(void* btn);
static void BtnOk_Single_Clicked_Handler(void* btn);
//BTN Timer callback
static void BtnTimerCb(void *para);

static void BtnUp_Single_Clicked_Handler(void* btn)
{
    uint32_t btn_event;

    btn_event = get_button_event((struct Button *)btn);

    switch (btn_event)
    {
    case SINGLE_CLICK:
        LCD_Fill(0,0, LCD_W,LCD_H,RED);
        PRO_LOG(LOG_DEBUG, "BTN UP SINGLE_CLICK. \r\n");
        break;

    case DOUBLE_CLICK:
    //    PRO_LOG(LOG_DEBUG, "BTN UP DOUBLE_CLICK. \r\n");
        break;

    case LONG_PRESS_START:
    //    PRO_LOG(LOG_DEBUG, "BTN UP LONG_PRESS_START. \r\n");
        break;

    case LONG_PRESS_HOLD:
    //    PRO_LOG(LOG_DEBUG, "BTN UP LONG_PRESS_HOLD. \r\n");
        break;

    default:
        break;
    }
}

static void BtnDown_Single_Clicked_Handler(void* btn)
{
    uint32_t btn_event;

    btn_event = get_button_event((struct Button *)btn);

    switch (btn_event)
    {
    case SINGLE_CLICK:
        LCD_Fill(0,0, LCD_W,LCD_H,GREEN);
        PRO_LOG(LOG_DEBUG, "BTN DOWN SINGLE_CLICK. \r\n");
        break;

    case DOUBLE_CLICK:
    //    PRO_LOG(LOG_DEBUG, "BTN DOWN DOUBLE_CLICK. \r\n");
        break;

    case LONG_PRESS_START:
    //    PRO_LOG(LOG_DEBUG, "BTN DOWN LONG_PRESS_START. \r\n");
        break;

    case LONG_PRESS_HOLD:
    //    PRO_LOG(LOG_DEBUG, "BTN DOWN LONG_PRESS_HOLD. \r\n");
        break;

    default:
        break;
    }
}

static void BtnLeft_Single_Clicked_Handler(void* btn)
{
    uint32_t btn_event;

    btn_event = get_button_event((struct Button *)btn);

    switch (btn_event)
    {
    case SINGLE_CLICK:
        LCD_Fill(0,0, LCD_W,LCD_H,BLUE);
        PRO_LOG(LOG_DEBUG, "BTN LEFT SINGLE_CLICK. \r\n");
        break;

    case DOUBLE_CLICK:
    //    PRO_LOG(LOG_DEBUG, "BTN LEFT DOUBLE_CLICK. \r\n");
        break;

    case LONG_PRESS_START:
    //    PRO_LOG(LOG_DEBUG, "BTN LEFT LONG_PRESS_START. \r\n");
        break;

    case LONG_PRESS_HOLD:
    //    PRO_LOG(LOG_DEBUG, "BTN LEFT LONG_PRESS_HOLD. \r\n");
        break;

    default:
        break;
    }
}

static void BtnRight_Single_Clicked_Handler(void* btn)
{
    uint32_t btn_event;

    btn_event = get_button_event((struct Button *)btn);

    switch (btn_event)
    {
    case SINGLE_CLICK:
        LCD_Fill(0,0, LCD_W,LCD_H,WHITE);
        PRO_LOG(LOG_DEBUG, "BTN RIGHT SINGLE_CLICK. \r\n");
        break;

    case DOUBLE_CLICK:
    //    PRO_LOG(LOG_DEBUG, "BTN RIGHT DOUBLE_CLICK. \r\n");
        break;

    case LONG_PRESS_START:
    //    PRO_LOG(LOG_DEBUG, "BTN RIGHT LONG_PRESS_START. \r\n");
        break;

    case LONG_PRESS_HOLD:
    //    PRO_LOG(LOG_DEBUG, "BTN RIGHT LONG_PRESS_HOLD. \r\n");
        break;

    default:
        break;
    }
}

static void BtnOk_Single_Clicked_Handler(void* btn)
{
    uint32_t btn_event;
    static bool sta = true;

    btn_event = get_button_event((struct Button *)btn);

    switch (btn_event)
    {
    case SINGLE_CLICK:
        sta = !sta;
        LCD_BackLight(sta);
        PRO_LOG(LOG_DEBUG, "BTN OK SINGLE_CLICK. \r\n");
        break;

    case DOUBLE_CLICK:
    //    PRO_LOG(LOG_DEBUG, "BTN OK DOUBLE_CLICK. \r\n");
        break;

    case LONG_PRESS_START:
    //    PRO_LOG(LOG_DEBUG, "BTN OK LONG_PRESS_START. \r\n");
        break;

    case LONG_PRESS_HOLD:
    //    PRO_LOG(LOG_DEBUG, "BTN OK LONG_PRESS_HOLD. \r\n");
        break;

    default:
        break;
    }
}

static void BtnTimerCb(void *para)
{
    button_ticks();
}

/**
 * @brief 按键端口初始化
 * 
 */
void KeyInit(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    /* Enable the GPIO Clock */
    RCC_EnableAPB2PeriphClk(KEY_RCC_PERIPH, ENABLE);

    GPIO_InitStructure.Pin        = KEY_UP_PIN | KEY_DOWN_PIN | KEY_LEFT_PIN | KEY_RIGHT_PIN | KEY_PRESSED_PIN;
    GPIO_InitStructure.GPIO_Pull    = GPIO_Pull_Up;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Input;
    GPIO_InitPeripheral(KEY_PORT_GROUP, &GPIO_InitStructure);
}

/**
 * @brief 获取按键状态
 * 
 * @param btn_id 按键ID
 * @return uint8_t 
 */
uint8_t KeyScan(uint8_t btn_id)
{
    switch (btn_id)
    {
    case KEY_UP_ID:
        return GPIO_ReadInputDataBit(KEY_PORT_GROUP, KEY_UP_PIN);
        break;
    
    case KEY_DOWN_ID:
        return GPIO_ReadInputDataBit(KEY_PORT_GROUP, KEY_DOWN_PIN);
        break;

    case KEY_LEFT_ID:
        return GPIO_ReadInputDataBit(KEY_PORT_GROUP, KEY_LEFT_PIN);
        break;

    case KEY_RIGHT_ID:
        return GPIO_ReadInputDataBit(KEY_PORT_GROUP, KEY_RIGHT_PIN);
        break;

    case KEY_PRESSED_ID:
        return GPIO_ReadInputDataBit(KEY_PORT_GROUP, KEY_PRESSED_PIN);
        break;

    default:
        break;
    }
    return 0xff;
}

/**
 * @brief 按键事件及回调注册
 * 
 * @return uint8_t 
 */
uint8_t KeyRegister(void)
{
    button_init(&dev_handler_s.dev_btn_s.btn_up, KeyScan, 0, KEY_UP_ID);
	button_init(&dev_handler_s.dev_btn_s.btn_down, KeyScan, 0, KEY_DOWN_ID);
    button_init(&dev_handler_s.dev_btn_s.btn_left, KeyScan, 0, KEY_LEFT_ID);
	button_init(&dev_handler_s.dev_btn_s.btn_right, KeyScan, 0, KEY_RIGHT_ID);
    button_init(&dev_handler_s.dev_btn_s.btn_ok, KeyScan, 0, KEY_PRESSED_ID);

    button_attach(&dev_handler_s.dev_btn_s.btn_up, SINGLE_CLICK,  BtnUp_Single_Clicked_Handler);
	button_attach(&dev_handler_s.dev_btn_s.btn_down, SINGLE_CLICK, BtnDown_Single_Clicked_Handler);
    button_attach(&dev_handler_s.dev_btn_s.btn_left, SINGLE_CLICK,  BtnLeft_Single_Clicked_Handler);
	button_attach(&dev_handler_s.dev_btn_s.btn_right, SINGLE_CLICK, BtnRight_Single_Clicked_Handler);
    button_attach(&dev_handler_s.dev_btn_s.btn_ok, SINGLE_CLICK,  BtnOk_Single_Clicked_Handler);
    button_attach(&dev_handler_s.dev_btn_s.btn_ok, DOUBLE_CLICK,  BtnOk_Single_Clicked_Handler);

    button_start(&dev_handler_s.dev_btn_s.btn_up);
	button_start(&dev_handler_s.dev_btn_s.btn_down);
    button_start(&dev_handler_s.dev_btn_s.btn_left);
	button_start(&dev_handler_s.dev_btn_s.btn_right);
    button_start(&dev_handler_s.dev_btn_s.btn_ok);

    dev_handler_s.dev_btn_s.btn_Timer = rt_timer_create("BTN Timer",
												BtnTimerCb,
												RT_NULL,
												5,
												RT_TIMER_FLAG_PERIODIC);
    if (dev_handler_s.dev_btn_s.btn_Timer != RT_NULL)
        rt_timer_start(dev_handler_s.dev_btn_s.btn_Timer);
}
