#ifndef __DEV_CTRL_H__
#define __DEV_CTRL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "multi_button.h"

/**@struct dev_btn_str
 * @brief 设备按键定义
 * 
 */
typedef struct {
    struct Button btn_up;
    struct Button btn_down;
    struct Button btn_left;
    struct Button btn_right;
    struct Button btn_ok;

    /* 定时器后台循环调用处理函数（5ms） */
    rt_timer_t btn_Timer;
}dev_btn_str;

/**@dev_handler_str
 * @brief 设备控制结构体
 * 
 */
typedef struct {
    dev_btn_str dev_btn_s;  /* 按键定义 */

}dev_handler_str;

#ifdef __cplusplus
}
#endif

#endif /* __DEV_CTRL_H__ */
