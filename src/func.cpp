#include <cstdint>
#include <cstddef>
#include "itm_write.h"
#include "rng.hpp"
#include "timer.hpp"
#include "stm32f4xx.h"
#include "core_cm4.h"
#include "types.hpp"

/* run from sram */
__attribute__((section(".SRAM2F"))) std::uint32_t ramFunc(std::uint32_t numA, std::uint32_t numB)
{
	return (numA + numB);
}

/* run from flash */
std::uint32_t ramFuncCCM(std::uint32_t numA, std::uint32_t numB)
{
	return (numA + numB);
}

static std::uint32_t timerValue = 0;
static hal_uc::timer* refTim;
static hal_uc::rng* refRng;


extern "C"
{
void printRandom(void)
{
	std::uint32_t randomNumberA = 0;

	refRng->getNumber(randomNumberA);

	printf("A %X  \n", randomNumberA);
}
}

static void cnt(void)
{
	timerValue++;

	if(timerValue >= 999)
	{
		timerValue = 0;
		printRandom();
	}
}



/* configure timer for about 1ms @APB1 Clock of 168Mhz / 4 (AHB Div) */
static hal_uc::timer::timConfig tim2Conf(
		hal_uc::timer::Instance::TIMER2,
		42-1,
		hal_uc::timer::CounterMode::UP,
		999,
		hal_uc::timer::ClockDiv::DIV1,
		0
		);


static simplePointer timerFunc = &cnt;

void initFunc(void)
{
	printf("Clock %u\n", SystemCoreClock);
	printf("Init RNG and Timers...\n");
	static hal_uc::rng rand1;
	static hal_uc::timer tim2(tim2Conf, timerFunc);

	refTim = &tim2;
	refRng = &rand1;
	printf("Start RNG and Timers...\n");
	rand1.start();
	tim2.start();
}



