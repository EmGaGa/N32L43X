#ifndef __KEY_H__
#define __KEY_H__

#ifdef __cplusplus
extern "C" {
#endif

#define KEY_PORT_GROUP      GPIOB
#define KEY_RCC_PERIPH      RCC_APB2_PERIPH_GPIOB

#define KEY_UP_PIN          GPIO_PIN_2
#define KEY_DOWN_PIN        GPIO_PIN_11
#define KEY_LEFT_PIN        GPIO_PIN_10
#define KEY_RIGHT_PIN       GPIO_PIN_1
#define KEY_PRESSED_PIN     GPIO_PIN_0

typedef enum {
    KEY_UP_ID = 0x00,
    KEY_DOWN_ID,
    KEY_LEFT_ID,
    KEY_RIGHT_ID,
    KEY_PRESSED_ID,

    /* MAX */
    KEY_MAX_ID
}KEY_TYPE_IDS;

void KeyInit(void);
uint8_t KeyScan(uint8_t btn_id);
uint8_t KeyRegister(void);

#ifdef __cplusplus
}
#endif

#endif /* __KEY_H__ */
