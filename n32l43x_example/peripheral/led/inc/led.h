#ifndef __LED_H__
#define __LED_H__

#ifdef __cplusplus
extern "C" {
#endif

//PA8,PB4,PB5
#define LED_PORT_GROUP1     GPIOA
#define LED_PORT_GROUP2     GPIOB
#define LED1_PORT           LED_PORT_GROUP1
#define LED2_PORT           LED_PORT_GROUP2
#define LED3_PORT           LED_PORT_GROUP2
#define LED1_PIN            GPIO_PIN_8
#define LED2_PIN            GPIO_PIN_4
#define LED3_PIN            GPIO_PIN_5

void LedInit(void);
void LedCtrl(uint8_t index, uint8_t sta);
void LedToggle(uint8_t index);
#ifdef __cplusplus
}
#endif

#endif /* __LED_H__ */
