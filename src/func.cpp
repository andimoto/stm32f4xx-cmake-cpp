#include <cstdint>
#include <cstddef>
#include "itm_write.h"

__attribute__((section(".RAM_FUNC"))) void ramFunc(std::uint32_t num)
{
	printf(" %s %X\n",__func__,num);
}
