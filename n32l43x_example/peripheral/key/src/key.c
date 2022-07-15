#include "header.h"

extern dev_handler_str dev_handler_s;

static int8_t color_index = 0;
const uint16_t color[21] = {WHITE, BLACK, BLUE, BRED, GRED, GBLUE, RED, MAGENTA,\
                        GREEN, CYAN, YELLOW, BROWN, BRRED, GRAY, DARKBLUE, \
                        LIGHTBLUE, GRAYBLUE, LIGHTGREEN, LGRAY, LGRAYBLUE, \
                        LBBLUE};

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
        if (--color_index < 0)
            color_index = 20;
        LCD_Fill(0,0, LCD_W,LCD_H,color[color_index]);
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
        if(++color_index > 20)
            color_index = 0;
        LCD_Fill(0,0, LCD_W,LCD_H,color[color_index]);
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

FATFS fs;//文件系统对象
FIL fp;//文件对象
char *write_text="FATFS test success!";
unsigned int write_bytes=0;
char read_buff[512];
unsigned int read_bytes=0;
BYTE work[FF_MAX_SS];

static void BtnLeft_Single_Clicked_Handler(void* btn)
{
    uint32_t btn_event;

    btn_event = get_button_event((struct Button *)btn);

    switch (btn_event)
    {
    case SINGLE_CLICK:
    {
        /* 打开文件，每次都以新建的形式打开，属性为可写 */
        PRO_LOG(LOG_DEBUG, "\r\n****** FATFS START WRITE... ******\r\n");	
        if(!f_open(&fp,"0:你好.txt",FA_CREATE_ALWAYS | FA_WRITE))
        {
            PRO_LOG(LOG_DEBUG, "open file success!\n");
        }
        else PRO_LOG(LOG_DEBUG, "open file failure!\n");
        
        if(!f_write(&fp,(char*)write_text,strlen(write_text),&write_bytes))
        {
            PRO_LOG(LOG_DEBUG, "write success,write_bytes=%d\n",write_bytes);
        }
        else PRO_LOG(LOG_DEBUG, "write failure!\n");
        if(!f_close(&fp))
        {
            PRO_LOG(LOG_DEBUG, "close success!\n");
        }
        else PRO_LOG(LOG_DEBUG, "close failure!\n");
    }
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
    FRESULT res;

    btn_event = get_button_event((struct Button *)btn);

    switch (btn_event)
    {
    case SINGLE_CLICK:
    {
        PRO_LOG(LOG_DEBUG, "\r\n****** FATFS START READ... ******\r\n");
        if(!f_open(&fp,"0:你好.txt",FA_READ))
        {
            PRO_LOG(LOG_DEBUG, "open file success!\n");
        }
        else PRO_LOG(LOG_DEBUG, "open file failure!\n");
        if(!f_read(&fp,(char*)read_buff,sizeof(read_buff),&read_bytes))
        {
            PRO_LOG(LOG_DEBUG, "read success,read_bytes=%d\n",read_bytes);
            PRO_LOG(LOG_DEBUG, "test.txt content is :%s\n",read_buff);
        }
        else PRO_LOG(LOG_DEBUG, "read failure!\n");
        if(!f_close(&fp))
        {
            PRO_LOG(LOG_DEBUG, "close success!\n");
        }
        else PRO_LOG(LOG_DEBUG, "close failure!\n");
    }
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

    FRESULT res_flash;

    btn_event = get_button_event((struct Button *)btn);

    switch (btn_event)
    {
    case SINGLE_CLICK:
    {
        res_flash = f_mount(&fs,"0:",1);
        
    /*----------------------- 格式化测试 -----------------*/  
        /* 如果没有文件系统就格式化创建创建文件系统 */
        if(res_flash == FR_NO_FILESYSTEM)
        {
            /* 格式化 */						
            res_flash = f_mkfs("0:", 0, work, sizeof(work));

            if(res_flash == FR_OK)
            {
                PRO_LOG(LOG_DEBUG, "f_mkfs success. \r\n");
                /* 格式化后，先取消挂载 */
                res_flash = f_mount(NULL,"0:",1);			
                /* 重新挂载	*/			
                res_flash = f_mount(&fs,"0:",1);
            }
            else
            {
                PRO_LOG(LOG_DEBUG, "f_mkfs failed.\r\n");
            }
        }
        else if(res_flash!=FR_OK)
        {
            PRO_LOG(LOG_DEBUG, "f_mount failed. (%d). \r\n", res_flash);
        }
        else
        {
            PRO_LOG(LOG_DEBUG, "f_mount init success, then start write and read test. \r\n");
        }
    }
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
