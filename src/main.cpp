#include "itm_write.h"
#include "rng.hpp"
#include "timer.hpp"
#include <cstdint>
#include <stdint.h>
#include "stm32f4xx.h"
#include "core_cm4.h"



extern std::uint32_t ramFunc(std::uint32_t numA, std::uint32_t numB);
extern std::uint32_t ramFuncCCM(std::uint32_t numA, std::uint32_t numB);

/* configure timer for about 1ms @APB1 Clock of 168Mhz / 4 (AHB Div) */
static hal_uc::timer::timConfig timConf(
		hal_uc::timer::Instance::TIMER2,
		42-1,
		hal_uc::timer::CounterMode::UP,
		999,
		hal_uc::timer::ClockDiv::DIV1,
		0,
		true
		);

static std::uint32_t timerValue = 0;

static hal_uc::timer* refTim;
static hal_uc::rng* refRng;

extern "C"
{
void printRandom(void)
{
	std::uint32_t randomNumber = 0;
	std::uint32_t randomNumberA = 0;
	std::uint32_t randomNumberB = 0;
	bool error = true;

	std::uint32_t timA = 0;
	std::uint32_t timB = 0;
	std::uint32_t timC = 0;
	std::uint32_t timD = 0;

	error = refRng->getNumber(randomNumberA);
	if(error != true)
		refRng->getNumber(randomNumberB);

	if(error != true)
	{
		timA = refTim->get();
		randomNumber = ramFunc(randomNumberA, randomNumberB);
		timB = refTim->get();
		printf("A %X in %u ticks\n", randomNumber, (timB-timA));

		timC = refTim->get();
		randomNumber = ramFuncCCM(randomNumberA, randomNumberB);
		timD = refTim->get();
		printf("B %X in %u ticks\n", randomNumber, (timD-timC));
	}
}
}

int main()
{
	hal_uc::rng rand1;
	hal_uc::timer tim2(timConf);

	refTim = &tim2;
	refRng = &rand1;

	rand1.start();
	tim2.start();

	printf("Clock %u\n", SystemCoreClock);

	for (;;)
	{
		if(timerValue >= 999)
		{
			timerValue = 0;
			printRandom();
		}
	};

	return 0;
}


extern "C" void TIM2_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	timerValue++;
}
