#ifndef USART_H
#define USART_H

//!< 送信データのポインタ
extern int8_t *usart1_tx_data;

//!< 受信データ
extern int8_t usart1_rx_data;

//!< usart1がデータを受信したかを示す
extern volatile int8_t usart1_rx_flag;

/**
 * @fn
 * usart1_initialize
 * @brief USART1を使用してシリアル通信を行うための初期設定を行う
 */
void usart1_initialize(void); 

/**
 * @fn
 * usart1_send_byte
 * @param byte 送信するデータ
 * @brief USART1を使用して1byte分のデータを送信する
 */
void usart1_send_byte(uint8_t byte);

/**
 * @fn
 * usart1_send_string
 * @param string[] 送信する文字列
 * @brief USART1を使用して文字列のデータを送信する
 */
void usart1_send_string(int8_t string[]);

#endif  
