#include <cstdint>
#include <stdint.h>

#include "itm_write.h"
#include "flash.hpp"
#include "timer.hpp"
#include "gpio.hpp"

extern std::uint32_t ramFunc(std::uint32_t numA, std::uint32_t numB);
extern std::uint32_t ramFuncCCM(std::uint32_t numA, std::uint32_t numB);
extern void initFunc(void);
extern void initGpio(void);
extern std::uint8_t getButtonK0(void);
extern std::uint8_t getButtonK1(void);

hal_uc::flash::memConfig sectorConf1(
		static_cast<std::uint32_t>(0x08000000),
		16384
		);

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
	std::uint32_t readAddress = 0x00000000;

	hal_uc::flash sector1(sectorConf1);
	hal_uc::timer tim3(tim3Conf, &countUp);
	initFunc();
	initGpio();

	sector1.getConfig();
	tim3.start();
//	printf("@ 0x%08X: 0x%08X\n", readAddress, sector1.read(0x08000000));


	for (;;)
	{
		if(counter >= 500)
		{
			counter = 0;

			if(getButtonK0() == 0)
			{
				printf("@ 0x%08X: 0x%08X\n", readAddress, sector1.read(readAddress));
				readAddress = readAddress + 4;
			}

			if(getButtonK1() == 0)
			{
				printf("Write to FLASH!\n");
				sector1.checkAddress(0x080000FF);
			}
		}
	};

	return 0;
}



