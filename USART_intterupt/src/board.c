#include "board.h"
#include "stm32f10x.h"

void board_led_initialize(void){
  // GPIO Configuration
  // Configure LED Pin
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void board_led_on(void){
  GPIO_SetBits(GPIOA, GPIO_Pin_5);
}

void board_led_off(void){
  GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}
