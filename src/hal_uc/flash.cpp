/**
 * Name: flash.cpp
 * Initial Author: andimoto
 */
#include "flash.hpp"
#include "itm_write.h"
#include "stm32f4xx_flash.h"

static std::uint32_t stm32f4FlashStartAddress = static_cast<std::uint32_t>(0x08000000);
static std::uint32_t stm32f40xSectorSizes[static_cast<std::uint8_t>(hal_uc::flash::flashSector::ALL_SECTORS)] = {
		static_cast<std::uint32_t>(1<<14),
		static_cast<std::uint32_t>(1<<14),
		static_cast<std::uint32_t>(1<<14),
		static_cast<std::uint32_t>(1<<14),
		static_cast<std::uint32_t>(1<<16),
		static_cast<std::uint32_t>(1<<17),
		static_cast<std::uint32_t>(1<<17),
		static_cast<std::uint32_t>(1<<17),
		static_cast<std::uint32_t>(1<<17),
		static_cast<std::uint32_t>(1<<17),
		static_cast<std::uint32_t>(1<<17),
		static_cast<std::uint32_t>(1<<17),
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0	/* invalid sector selection */
};

static std::uint8_t getNextSector(const hal_uc::flash::flashSector thisSector, hal_uc::flash::flashSector& nextSector)
{
	std::uint8_t error = 1;

	switch(thisSector)
	{
	case hal_uc::flash::flashSector::FSECTOR_00: nextSector = hal_uc::flash::flashSector::FSECTOR_01; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_01: nextSector = hal_uc::flash::flashSector::FSECTOR_02; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_02: nextSector = hal_uc::flash::flashSector::FSECTOR_03; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_03: nextSector = hal_uc::flash::flashSector::FSECTOR_04; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_04: nextSector = hal_uc::flash::flashSector::FSECTOR_05; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_05: nextSector = hal_uc::flash::flashSector::FSECTOR_06; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_06: nextSector = hal_uc::flash::flashSector::FSECTOR_07; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_07: nextSector = hal_uc::flash::flashSector::FSECTOR_08; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_08: nextSector = hal_uc::flash::flashSector::FSECTOR_09; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_09: nextSector = hal_uc::flash::flashSector::FSECTOR_10; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_10: nextSector = hal_uc::flash::flashSector::FSECTOR_11; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_11: nextSector = hal_uc::flash::flashSector::FSECTOR_12; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_12: nextSector = hal_uc::flash::flashSector::FSECTOR_13; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_13: nextSector = hal_uc::flash::flashSector::FSECTOR_14; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_14: nextSector = hal_uc::flash::flashSector::FSECTOR_15; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_15: nextSector = hal_uc::flash::flashSector::FSECTOR_16; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_16: nextSector = hal_uc::flash::flashSector::FSECTOR_17; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_17: nextSector = hal_uc::flash::flashSector::FSECTOR_18; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_18: nextSector = hal_uc::flash::flashSector::FSECTOR_19; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_19: nextSector = hal_uc::flash::flashSector::FSECTOR_20; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_20: nextSector = hal_uc::flash::flashSector::FSECTOR_21; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_21: nextSector = hal_uc::flash::flashSector::FSECTOR_22; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_22: nextSector = hal_uc::flash::flashSector::FSECTOR_23; error = 0; break;
	case hal_uc::flash::flashSector::FSECTOR_23: nextSector = hal_uc::flash::flashSector::ALL_SECTORS; error = 0; break;
	default: error = 1; break;
	}

	return error;
}

static std::uint8_t getSectorStart(const hal_uc::flash::flashSector sector, std::uint32_t& sectorStartAddress)
{
	std::uint8_t error = 1;
	std::uint32_t sectorAddress = 0;
	hal_uc::flash::flashSector nextSector = hal_uc::flash::flashSector::ALL_SECTORS;
	hal_uc::flash::flashSector currentSector = hal_uc::flash::flashSector::ALL_SECTORS;

	sectorAddress = stm32f4FlashStartAddress;

	if(sector == hal_uc::flash::flashSector::FSECTOR_00)
	{
		sectorStartAddress = stm32f4FlashStartAddress;
	}else{
		currentSector = hal_uc::flash::flashSector::FSECTOR_00;
		error = getNextSector(currentSector, nextSector);

		while(static_cast<std::uint32_t>(nextSector) <= static_cast<std::uint32_t>(sector)
				|| error == 1)
		{
			sectorAddress = sectorAddress + stm32f40xSectorSizes[static_cast<std::uint8_t>(currentSector)];
			currentSector = nextSector;
			error = getNextSector(currentSector, nextSector);
		}
	}
//	printf("Sector %u Address: 0x%08X\n",static_cast<std::uint8_t>(sector), sectorAddress);

	return error;
}


static FLASH_Status getFlashStatus(void)
{
	__IO FLASH_Status flashstatus = FLASH_COMPLETE;

	if((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY)
	{
		flashstatus = FLASH_BUSY;
	}
	else
	{
		if((FLASH->SR & FLASH_FLAG_WRPERR) != (uint32_t)0x00)
		{
			flashstatus = FLASH_ERROR_WRP;
		}
		else
		{
			if((FLASH->SR & FLASH_FLAG_RDERR) != (uint32_t)0x00)
			{
				flashstatus = FLASH_ERROR_RD;
			}
			else
			{
				if((FLASH->SR & (uint32_t)0xE0) != (uint32_t)0x00)
				{
					flashstatus = FLASH_ERROR_PROGRAM;
				}
				else
				{
					if((FLASH->SR & FLASH_FLAG_OPERR) != (uint32_t)0x00)
					{
						flashstatus = FLASH_ERROR_OPERATION;
					}
					else
					{
						flashstatus = FLASH_COMPLETE;
					}
				}
			}
		}
	}
	/* Return the FLASH Status */
	return flashstatus;
}

static FLASH_Status flashStatus(void)
{
	FLASH_Status flashStat = FLASH_COMPLETE;

	flashStat = getFlashStatus();

	while(flashStat == FLASH_BUSY)
	{
		flashStat = getFlashStatus();
	}

	return flashStat;
}


hal_uc::flash::memConfig::memConfig(const std::uint32_t startAddrConf, const std::uint32_t secSizeConf):
	startAddr(startAddrConf), secSize(secSizeConf)
{

}


//hal_uc::flash::memConfig::memConfig(const hal_uc::flash::flashSector sectorNo):
//	startAddr(getSectorStart(sectorNo)), secSize(getSectorSize(sectorNo))
//{
//
//}

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

std::uint32_t hal_uc::flash::read(const std::uint32_t rdAddr)
{
	std::uint32_t data = 0;

	data = *(__IO std::uint32_t*)rdAddr;

	return data;
}

bool hal_uc::flash::checkAddress(const std::uint32_t checkAddress)
{
	bool addrValid = false;
	hal_uc::flash::flashSector sector = flashSector::FSECTOR_00;
	hal_uc::flash::flashSector nextSector = flashSector::FSECTOR_00;
	std::uint32_t sectorStartAddress;
//	printf("Sector %u: 0x%08X\n",
//			static_cast<std::uint8_t>(sector),
//			stm32f40xSectorSizes[static_cast<std::uint8_t>(sector)]
//					   );
	while(sector != hal_uc::flash::flashSector::ALL_SECTORS)
	{
		getSectorStart(sector, sectorStartAddress);
		getNextSector(sector, nextSector);
		sector = nextSector;
	}
//	printf("*** All Addresses ***\n");
	return addrValid;
}

bool hal_uc::flash::writeWord(const std::uint32_t wrAddr, const std::uint32_t wrData)
{
	FLASH_Status status = FLASH_COMPLETE;
	bool opDone = false;

	opDone = checkAddress(wrAddr);

	status = flashStatus();

	if(opDone == true && status == FLASH_COMPLETE)
	{
		FLASH->CR &= CR_PSIZE_MASK;
		FLASH->CR |= FLASH_PSIZE_WORD;
		FLASH->CR |= FLASH_CR_PG;

		*(__IO uint32_t*)wrAddr = wrData;

		/* Wait for last operation to be completed */
		status = flashStatus();

		/* if the program operation is completed, disable the PG Bit */
		FLASH->CR &= (~FLASH_CR_PG);

		opDone = true;
	}else{
		opDone = false;
	}
	return opDone;
}

bool hal_uc::flash::eraseSector(const hal_uc::flash::flashSector sector)
{
	return true;
}


