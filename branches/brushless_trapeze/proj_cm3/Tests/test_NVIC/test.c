#include "stm_system.h"

int main(void)
{
	NVIC_SET_PRIO_PERIPH(USART1,1);

	NVIC_SET_PRIO_SYSTEM(MEM_FAULT,15);
	NVIC_SET_PRIO_SYSTEM(BUS_FAULT,14);
	NVIC_SET_PRIO_SYSTEM(USAGE_FAULT,13);
	NVIC_SET_PRIO_SYSTEM(SVCALL,12);
	NVIC_SET_PRIO_SYSTEM(DEBUG,11);
	NVIC_SET_PRIO_SYSTEM(PENDSV,10);
	NVIC_SET_PRIO_SYSTEM(SYSTICK,9);

	NVIC_ENABLE_SYSTEM_IT(MEM_FAULT);
	NVIC_ENABLE_SYSTEM_IT(BUS_FAULT);
	NVIC_ENABLE_SYSTEM_IT(USAGE_FAULT);
	NVIC_ENABLE_SYSTEM_IT(SYSTICK);

	for (;;);
}