#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "system_stm32f10x.h"

static volatile uint32_t TimeDelay;

void Delay(volatile uint32_t nTime);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval : None
  */
int main(void){
  SystemInit();
  
  // GPIO Configuration
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_SetBits(GPIOA, GPIO_Pin_5);
  
  if(SysTick_Config(SystemCoreClock / 1000)){
    while(1);
  }

  while (1)
  {
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
    Delay(100);
    GPIO_SetBits(GPIOA, GPIO_Pin_5);
    Delay(100);
  }
}

void Delay(volatile uint32_t nTime){
  TimeDelay = nTime;
  while(TimeDelay != 0);
}

void TimeDelay_Decrement(void){
  if(TimeDelay != 0x00){
    TimeDelay--;
  }
}

