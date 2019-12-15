#include "itm_write.h"
#include "rng.hpp"
#include "timer.hpp"
#include <cstdint>
#include <stdint.h>
#include "stm32f4xx.h"
#include "core_cm4.h"

extern std::uint32_t ramFunc(std::uint32_t numA, std::uint32_t numB);
extern std::uint32_t ramFuncCCM(std::uint32_t numA, std::uint32_t numB);

static hal_uc::timer::timConfig timConf(
		hal_uc::timer::Instance::TIMER2,
		83,
		hal_uc::timer::CounterMode::UP,
		1000,
		hal_uc::timer::ClockDiv::DIV2,
		0,
		true
		);

void TIM2_IRQHandler(void)
{
	NVIC_SetPendingIRQ(TIM2_IRQn);
	printf("*");
}


int main()
{
	unsigned int a = 0;
	std::uint32_t randomNumber = 0;
	std::uint32_t randomNumberA = 0;
	std::uint32_t randomNumberB = 0;
	bool error = true;

	std::uint32_t timA = 0;
	std::uint32_t timB = 0;
	std::uint32_t timC = 0;
	std::uint32_t timD = 0;

	hal_uc::rng rand1;
	hal_uc::timer tim2(timConf);

	rand1.start();
	tim2.start();

	for (;;)
	{
		a++;

		if(a==2000000)
		{
			a = 0;
			error = rand1.getNumber(randomNumberA);
			if(error != true)
				rand1.getNumber(randomNumberB);

			if(error != true)
			{
				timA = tim2.get();
				randomNumber = ramFunc(randomNumberA, randomNumberB);
				timB = tim2.get();
				printf("A %X in %u ticks\n", randomNumber, (timB-timA));

				timC = tim2.get();
				randomNumber = ramFuncCCM(randomNumberA, randomNumberB);
				timD = tim2.get();
				printf("B %X in %u ticks\n", randomNumber, (timD-timC));
			}
		}
	};

	return 0;
}
