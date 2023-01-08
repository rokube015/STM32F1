#include "delay.h"
#include "stm32f10x.h"
#include "system_stm32f10x.h"

//!< ディレイ時間をカウントするグローバル変数
static volatile uint32_t Delay_time;

void initialize_systickTimer(void){
  if(SysTick_Config(SystemCoreClock / 1000)){
    while(1);
  }
}

void delay_ms(volatile uint32_t delay_time_ms){
  Delay_time = delay_time_ms;
  while(Delay_time != 0x00);
}

void decrese_delay_time(void){
  if(Delay_time != 0x00){
    Delay_time--;
  }
}

