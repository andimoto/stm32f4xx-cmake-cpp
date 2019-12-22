#include <cstdint>
#include <stdint.h>

#include "itm_write.h"


extern std::uint32_t ramFunc(std::uint32_t numA, std::uint32_t numB);
extern std::uint32_t ramFuncCCM(std::uint32_t numA, std::uint32_t numB);
extern void initFunc(void);


int main()
{
	initFunc();

	for (;;)
	{

	};

	return 0;
}



