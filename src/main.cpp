#include "stm32f4xx.h"

int main()
{
	int a = 0;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef gpio_out = {
		.GPIO_Pin = GPIO_Pin_2,
		.GPIO_Mode = GPIO_Mode_OUT,
		.GPIO_Speed = GPIO_High_Speed,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd = GPIO_PuPd_NOPULL
	};

	GPIO_Init(GPIOD, &gpio_out);
	GPIO_WriteBit(GPIOD, GPIO_Pin_2, Bit_SET);



	for (;;)
	{
		a++;


		if(a==100000)
		{
			a = 0;

			GPIO_ToggleBits(GPIOD, GPIO_Pin_2);
		}
	};

	return 0;
}
