#include <cstdint>
#include <cstddef>
#include "itm_write.h"

__attribute__((section(".SRAM2F"))) std::uint32_t ramFunc(std::uint32_t numA, std::uint32_t numB)
{
	return (numA + numB);
}


//__attribute__((section(".CCMEM"))) std::uint32_t ramFuncCCM(std::uint32_t numA, std::uint32_t numB)
//{
//	return (numA + numB);
//}
