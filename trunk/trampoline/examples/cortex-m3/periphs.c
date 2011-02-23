#include "stm_regs.h"

void Init_Periphs(void)
{
	(RCC->APB2ENR)=(RCC->APB2ENR) | RCC_IOPAEN | RCC_IOPBEN | RCC_IOPCEN;

  //EXTI0 sur PA0 (bouton wakeup de MCB)
  EXTI->IMR |= 1;
  EXTI->RTSR |= 1;
  NVIC_ENABLE_PERIPH_IT(EXTI0); 
  NVIC_SET_PRIO_PERIPH(EXTI0,1);

// Diodes
	GPIOB->CRH &= ~0xFFF	;
  	GPIOB->CRH |= (GPIO_MODE_OUTPUT_10_MHZ << GPIO_MODE_8_SHIFT) | (GPIO_CNF_OUTPUT_PUSH_PULL << GPIO_CNF_8_SHIFT);
  	GPIOB->CRH |= (GPIO_MODE_OUTPUT_10_MHZ << GPIO_MODE_9_SHIFT) | (GPIO_CNF_OUTPUT_PUSH_PULL << GPIO_CNF_9_SHIFT);
 	GPIOB->CRH |= (GPIO_MODE_OUTPUT_10_MHZ << GPIO_MODE_10_SHIFT) | (GPIO_CNF_OUTPUT_PUSH_PULL << GPIO_CNF_10_SHIFT);

}

