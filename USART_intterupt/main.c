#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "system_stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "board.h"
#include "nvic.h"

#define countof           (sizeof(a)  / sizeof(*(a)))

const int8_t Welcome_Message[] = "\r\nHellow Cortex-M3/STM32 World!\r\n"
                "Expand your creativity and enjoy making.\r\n\r\n";

int8_t *tx_data;

int main(void){
  SystemInit();
  initialize_systickTimer();
  board_led_initialize();
  board_led_on();

  nvic_priority_group_configuration();
  nvic_usart1_configuration();

  usart1_initialize();
  usart1_send_string(Welcome_Message);
  //wait 1000ms
  delay_ms(1000);
  
  USART_ClearITPendingBit(USART1, USART_IT_RXNE);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

  while (1){
    if(usart1_rx_flag != 0){
      usart1_send_string(&usart1_rx_data);
      usart1_rx_flag = 0; 
    }
  }
}




