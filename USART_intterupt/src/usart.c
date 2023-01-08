#include "stdint.h"

#include "stm32f10x.h"
#include "usart.h"

int8_t *usart1_tx_data;
int8_t usart1_rx_data;
volatile int8_t usart1_rx_flag = 0;

void usart1_initialize(void){
  // enable gpio port clock 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

  // configure usart1 pin
  GPIO_InitTypeDef gpio_init_structure;

  gpio_init_structure.GPIO_Pin = GPIO_Pin_9;
  gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_init_structure.GPIO_Mode=GPIO_Mode_AF_PP;

  GPIO_Init(GPIOA, &gpio_init_structure);

  gpio_init_structure.GPIO_Pin = GPIO_Pin_10;
  gpio_init_structure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &gpio_init_structure);

  // configure usart1
  USART_InitTypeDef usart_init_structure;

  usart_init_structure.USART_BaudRate = 115200;
  usart_init_structure.USART_WordLength = USART_WordLength_8b;
  usart_init_structure.USART_StopBits = USART_StopBits_1;
  usart_init_structure.USART_Parity = USART_Parity_No;
  usart_init_structure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  usart_init_structure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &usart_init_structure); 
  USART_Cmd(USART1, ENABLE);
}

void usart1_send_byte(uint8_t Byte){
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
  USART_SendData(USART1, Byte);
}

void usart1_send_string(const int8_t string[]){
  usart1_tx_data = (int8_t *)string;
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
}


