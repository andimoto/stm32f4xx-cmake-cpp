#include <cstdint>
#include <cstddef>
#include "itm_write.h"

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
