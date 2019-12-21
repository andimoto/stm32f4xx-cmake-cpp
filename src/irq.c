#include <stdint.h>
#include "stm32f4xx.h"
#include "core_cm4.h"

extern uint32_t timerValue;
extern void printRandom(void);

void TIM2_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

	timerValue++;
//	printRandom();
//	printf("%u\n",t++);
}
