#include <cstdint>
#include <stdint.h>

#include "itm_write.h"
#include "flash.hpp"
#include "timer.hpp"
#include "gpio.hpp"
#include "keyPad.hpp"


/* configure timer for about 1ms @APB1 Clock of 168Mhz / 4 (AHB Div) */
static hal_uc::timer::timConfig tim3Conf(
		hal_uc::timer::Instance::TIMER3,
		42-1,
		hal_uc::timer::CounterMode::UP,
		1000,
		hal_uc::timer::ClockDiv::DIV1,
		0
		);

static std::uint32_t counter = 0;
static void countUp(void)
{
	counter++;
}

int main()
{
	hal_uc::timer tim3(tim3Conf, &countUp);
	tim3.start();

	for (;;)
	{
		if(counter > 500)
		{
			counter = 0;
			printf("Hello!\n");
		}
	};

	return 0;
}



