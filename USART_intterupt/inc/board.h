#ifndef BOARD_H
#define BOARD_H

/**
 * @fn
 * bord_led_initialize
 * @brief nucleoのボード上のLEDを使用するための初期設定を行う
 */
void board_led_initialize(void);

/**
 * @fn
 * bord_led_on
 * @brief nucleoのボード上のLEDを点灯する
 */
void board_led_on(void);

/**
 * @fn
 * bord_led_off
 * @brief nucleoのボード上のLEDを消灯する
 */
void board_led_off(void);

#endif
