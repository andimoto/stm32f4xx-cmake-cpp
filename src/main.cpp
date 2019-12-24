#include <cstdint>
#include <stdint.h>

#include "itm_write.h"
#include "flash.hpp"

extern std::uint32_t ramFunc(std::uint32_t numA, std::uint32_t numB);
extern std::uint32_t ramFuncCCM(std::uint32_t numA, std::uint32_t numB);
extern void initFunc(void);
extern void initGpio(void);

hal_uc::flash::memConfig sectorConf1(
		static_cast<std::uint32_t>(0x08000000),
		16384
		);


int main()
{
	hal_uc::flash sector1(sectorConf1);

	initFunc();
	initGpio();

	sector1.getConfig();

	for (;;)
	{

	};

	return 0;
}



