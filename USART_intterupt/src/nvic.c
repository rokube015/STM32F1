#include "nvic.h"
#include "stm32f10x.h"

void nvic_priority_group_configuration(void){
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
}

void nvic_usart1_configuration(void){
  NVIC_InitTypeDef nvic_init_structure;

  nvic_init_structure.NVIC_IRQChannel = USART1_IRQn;
  nvic_init_structure.NVIC_IRQChannelSubPriority = 0;
  nvic_init_structure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic_init_structure);
}

