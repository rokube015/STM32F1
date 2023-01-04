#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "system_stm32f10x.h"
#include "delay.h"

#define countof           (sizeof(a)  / sizeof(*(a)))

const int8_t Welcome_Message[] = "\r\nHellow Cortex-M3/STM32 World!\r\n"
                "Expand your creativity and enjoy making.\r\n\r\n"
                "Type anything. I send back you what you type, "
                "while I toggle my LED and plus 1 on nuric numbers.\r\n";

uint8_t RxData;

void USART1_Send_Byte(uint8_t Byte);
void USART1_Send_String(const int8_t String[]);

int main(void){
  SystemInit();
  initialize_systickTimer();

  // Clock Configuration
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
  
  // GPIO Configuration
  // Configure LED Pin
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // Configure USART1 Tx as input floating
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  // Configure USART1 Rx as input floating
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // USART1 Configuration
  USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure);
  USART_Cmd(USART1, ENABLE);
 
  USART1_Send_String(Welcome_Message);
  //GPIO_SetBits(GPIOA, GPIO_Pin_5);
  
  while (1){
    if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET){
      RxData = (int8_t)USART_ReceiveData(USART1);

      if(RxData >= 0x30 && RxData <= 0x38)
        RxData++;
      else if(RxData == 0x39)
        RxData = 0x30;
      
      delay_ms(1000);

      USART1_Send_Byte(RxData);
      // toggle on-board led
      if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_5))
      {
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
      }
      else
      {
        GPIO_SetBits(GPIOA, GPIO_Pin_5);
      }
    }
  }
}

void USART1_Send_Byte(uint8_t Byte){
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
  USART_SendData(USART1, Byte);
}

void USART1_Send_String(const int8_t String[])
{
  uint8_t i = 0;
  while (String[i] != '\0'){
    //Send data via USART1
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, String[i]);
    i++;
  }
}

