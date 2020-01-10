#include <cstdint>
#include <stdint.h>

#include "itm_write.h"
#include "flash.hpp"
#include "timer.hpp"
#include "gpio.hpp"
#include "keyPad.hpp"

extern std::uint32_t ramFunc(std::uint32_t numA, std::uint32_t numB);
extern std::uint32_t ramFuncCCM(std::uint32_t numA, std::uint32_t numB);
extern void initFunc(void);
extern void initGpio(void);
extern std::uint8_t getButtonK0(void);
extern std::uint8_t getButtonK1(void);
extern std::uint8_t getButtonKUP(void);

hal_uc::flash::memConfig sectorConf1(
		hal_uc::flash::flashSector::FSECTOR_05
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
	/* experimental firmware */

	std::uint32_t readAddress = 0x08020000;
	std::uint32_t freeReadAddress = 0x08000000;

	std::uint8_t K0 = 0;
	std::uint8_t previousK0 = 0;
	std::uint8_t K1 = 0;
	std::uint8_t previousK1 = 0;
	std::uint8_t KUP = 0;
	std::uint8_t previousKUP = 0;

	hal_uc::flash sector1(sectorConf1);
	hal_uc::timer tim3(tim3Conf, &countUp);
	initFunc();
	initGpio();

	sector1.printSectorConfig();
	tim3.start();


	for (;;)
	{
		if(counter > 500)
		{
			counter = 0;

			/* ----- Button K1 ----- */
			previousK0 = K0;
			K0 = getButtonK0();

			if(K0 == 0 && previousK0 == 1)
			{
				std::uint32_t rdData = 0;
				if(sector1.read(readAddress, rdData))
				{
					printf("@ 0x%08X: 0x%08X | @ 0x%08X: 0x%08X\n", readAddress, rdData, freeReadAddress, hal_uc::flash::freeRead(freeReadAddress));
					readAddress = readAddress + 4;
					freeReadAddress = freeReadAddress + 4;
				}else{
					printf("Invalid Address!\n");
				}
			}


			/* ----- Button K1 ----- */
			previousK1 = K1;
			K1 = getButtonK1();

			/* on falling edge of K1 write into flash section */
			if(K1 == 0 && previousK1 == 1)
			{
				static std::uint32_t writeToAddress = 0x08020000;
				static std::uint32_t writeData = 0x00000001;
				bool done = false;
				printf("Write word 0x%08X to 0x%08X!\n", writeData, writeToAddress);
				done = sector1.writeWord(writeToAddress, writeData);

				if(done == false)
				{
					printf("Write error!\n");
				}else{
					writeData++;
					writeToAddress = writeToAddress + sizeof(writeData);
				}
			}

			/* ----- Button KUP ----- */
			previousKUP = KUP;
			KUP = getButtonKUP();

			if(KUP == 1 && previousKUP == 0)
			{
				bool done = false;
				printf("Do erase sector!\n");
				done = sector1.eraseSector();
				if(done == false)
				{
					printf("Failure! Could not erase sector!\n");
				}else{
					/* reset read address */
					readAddress = 0x08020000;
				}
			}

			progressKeyPad4x4();
		}
	};

	return 0;
}



