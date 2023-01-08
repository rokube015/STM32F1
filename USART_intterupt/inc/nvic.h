#ifndef NVIC_H
#define NVIC_H

/**
 * @fn
 * nvic_priority_group_configuration
 * @brief NVICグループ優先度の設定を行う
 */
void nvic_priority_group_configuration(void);

/**
 * @fn
 * nvic_usart1_configuration
 * @brief usart1の割り込みの設定を行う
 */
void nvic_usart1_configuration(void);

#endif
