#include <cstdint>
#include <stdint.h>

#include "itm_write.h"


extern std::uint32_t ramFunc(std::uint32_t numA, std::uint32_t numB);
extern std::uint32_t ramFuncCCM(std::uint32_t numA, std::uint32_t numB);
extern void initFunc(void);
extern void initGpio(void);

int main()
{
	initFunc();
	initGpio();
	for (;;)
	{

	};

	return 0;
}



