#include <stdint.h>

/**
 * @fn
 * initialize_systickTimer
 * @brief delay_ms関数を使用するために、systickTimerの設定を行う.
 */
void initialize_systickTimer(void);

/**
 * @fn
 * delay_time_ms
 * @brief 引数で指定した時間、処理を遅延する
 * @param (delay_time_ms) 遅延させる時間[ms]
 */
void delay_ms(volatile uint32_t delay_time_ms);

/**
 * @fn
 * decrese_delay_time
 * @brief グローバル変数Delay_timeをディクリメントする関数.割り込み関数SysTick_Handlerから呼ばれる.
 */
void decrese_delay_time(void);


