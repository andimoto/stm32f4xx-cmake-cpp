/**
 * Name: flash.cpp
 * Initial Author: andimoto
 */
#include "flash.hpp"
#include "itm_write.h"

hal_uc::flash::memConfig::memConfig(const std::uint32_t startAddrConf, const std::uint32_t secSizeConf):
	startAddr(startAddrConf), secSize(secSizeConf)
{

}


hal_uc::flash::flash(const hal_uc::flash::memConfig& sector):
		startAddress(sector.startAddr), sectorSize(sector.secSize)
{

}


void hal_uc::flash::getConfig(void)
{
	printf("%s\n", __func__);
	printf("Start: 0x%08X\n", startAddress);
	printf("Size: %u Byte\n", sectorSize);
}
