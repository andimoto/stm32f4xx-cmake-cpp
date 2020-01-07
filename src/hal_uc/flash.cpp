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

static std::uint32_t getSectorStart(const hal_uc::flash::flashSector sector)
{
	std::uint8_t error = 1;
	std::uint32_t sectorAddress = 0;
	hal_uc::flash::flashSector nextSector = hal_uc::flash::flashSector::ALL_SECTORS;
	hal_uc::flash::flashSector currentSector = hal_uc::flash::flashSector::ALL_SECTORS;

	sectorAddress = stm32f4FlashStartAddress;

	if(sector == hal_uc::flash::flashSector::FSECTOR_00)
	{

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

		if(error == 1)
		{
			/* return address 0xFFFFFFFF if error occurred */
			sectorAddress = static_cast<std::uint32_t>(0xFFFFFFFF);
		}
	}

	return sectorAddress;
}



static void flashUnlock(void)
{
  if((FLASH->CR & FLASH_CR_LOCK) != RESET)
  {
    /* Authorize the FLASH Registers access */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
  }
}

static void flashLock(void)
{
  /* Set the LOCK Bit to lock the FLASH Registers access */
  FLASH->CR |= FLASH_CR_LOCK;
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


hal_uc::flash::memConfig::memConfig(const hal_uc::flash::flashSector sectorNo):
		userSectorConfig(sectorNo)
{

}

hal_uc::flash::flash(const hal_uc::flash::memConfig& sector):
		userSector(sector.userSectorConfig), startAddress(getSectorStart(sector.userSectorConfig)),
		sectorSize(stm32f40xSectorSizes[static_cast<std::uint8_t>(sector.userSectorConfig)])
{
	/* if startAddress is "not invalid" */
	if(startAddress == 0xFFFFFFFF)
	{
		/* error! */
	}
}

void hal_uc::flash::printSectorConfig(void)
{
	printf("%s\n", __func__);
	printf("Start: 0x%08X\n", startAddress);
	printf("Start: 0x%08X\n", startAddress + sectorSize - 1);
	printf("Size: %u Byte\n", sectorSize);
}

std::uint32_t hal_uc::flash::freeRead(const std::uint32_t rdAddr)
{
	std::uint32_t data = 0;

	data = *(__IO std::uint32_t*)rdAddr;

	return data;
}

bool hal_uc::flash::read(const std::uint32_t rdAddr, std::uint32_t& rdData)
{
	bool addrValid = true;

	if(rdAddr >= startAddress &&
			rdAddr < (startAddress + sectorSize))
	{
		rdData = *(__IO std::uint32_t*)rdAddr;
	}else{
		addrValid = false;
	}

	return addrValid;
}

bool hal_uc::flash::checkAddress(const std::uint32_t checkAddress)
{
	bool addrValid = false;

	if(checkAddress >= startAddress &&
			checkAddress < (startAddress + sectorSize))
	{
		addrValid = true;
	}


	return addrValid;
}

/*__attribute__((section(".SRAM2F"))) */ static FLASH_Status writeToFlash(const std::uint32_t wrAddr, const std::uint32_t wrData)
{
	FLASH_Status status = FLASH_COMPLETE;
	FLASH->CR &= CR_PSIZE_MASK;
	FLASH->CR |= FLASH_PSIZE_WORD;
	FLASH->CR |= FLASH_CR_PG;

	*(__IO uint32_t*)wrAddr = wrData;

	/* Wait for last operation to be completed */
	status = flashStatus();

	/* if the program operation is completed, disable the PG Bit */
	FLASH->CR &= (~FLASH_CR_PG);

	return status;
}

bool hal_uc::flash::writeWord(const std::uint32_t wrAddr, const std::uint32_t wrData)
{
	FLASH_Status status = FLASH_COMPLETE;
	bool opDone = false;

	/* check if address is in used flash section */
	opDone = checkAddress(wrAddr);

	status = flashStatus();

	if(opDone == true && status == FLASH_COMPLETE)
	{
		/* unlock flash before write */
		flashUnlock();

		/* write to flash */
		status = writeToFlash(wrAddr, wrData);

		/* lock flash to avoid unintended write */
		flashLock();

		if(status == FLASH_COMPLETE)
		{
			opDone = true;
		}
	}
	return opDone;
}

bool hal_uc::flash::eraseSector(void)
{
	bool opDone = 0;
	std::uint32_t eraseSector = 0;
	FLASH_Status status = FLASH_COMPLETE;
	/*
	 * change this if using other voltage range
	 * VoltageRange_1: when the device voltage range is 1.8V to 2.1V,
	 * VoltageRange_2: when the device voltage range is 2.1V to 2.7V,
	 * VoltageRange_3: when the device voltage range is 2.7V to 3.6V,
	 * VoltageRange_4: when the device voltage range is 2.7V to 3.6V + External Vpp
	 * */
	constexpr std::uint8_t deviceVoltageRange = VoltageRange_3;

	constexpr std::uint32_t voltageMaskArray[4] = {
			FLASH_PSIZE_BYTE,
			FLASH_PSIZE_HALF_WORD,
			FLASH_PSIZE_WORD,
			FLASH_PSIZE_DOUBLE_WORD
	};

	/* sector mask for erase */
	std::uint16_t stm32f40xSectorEraseMasks[static_cast<std::uint8_t>(hal_uc::flash::flashSector::ALL_SECTORS)] = {
			static_cast<std::uint16_t>(0x0000),	static_cast<std::uint16_t>(0x0008),	static_cast<std::uint16_t>(0x0010),
			static_cast<std::uint16_t>(0x0018),	static_cast<std::uint16_t>(0x0020),	static_cast<std::uint16_t>(0x0028),
			static_cast<std::uint16_t>(0x0030),	static_cast<std::uint16_t>(0x0038),	static_cast<std::uint16_t>(0x0040),
			static_cast<std::uint16_t>(0x0048),	static_cast<std::uint16_t>(0x0050),	static_cast<std::uint16_t>(0x0058),
			static_cast<std::uint16_t>(0x0080),	static_cast<std::uint16_t>(0x0088),	static_cast<std::uint16_t>(0x0090),
			static_cast<std::uint16_t>(0x0098),	static_cast<std::uint16_t>(0x00A0),	static_cast<std::uint16_t>(0x00A8),
			static_cast<std::uint16_t>(0x00B0),	static_cast<std::uint16_t>(0x00B8),	static_cast<std::uint16_t>(0x00C0),
			static_cast<std::uint16_t>(0x00C8),	static_cast<std::uint16_t>(0x00D0),	static_cast<std::uint16_t>(0x00D8)
	};

	constexpr std::uint32_t voltageMask = voltageMaskArray[static_cast<std::uint8_t>(deviceVoltageRange)];
	constexpr std::uint32_t SECTOR_MASK = static_cast<std::uint32_t>(0xFFFFFF07);

	/* Wait for last operation to be completed */
	status = flashStatus();

	eraseSector = stm32f40xSectorEraseMasks[static_cast<std::uint32_t>(this->userSector)];

	if(status == FLASH_COMPLETE)
	{
		flashUnlock();

		/* if the previous operation is completed, proceed to erase the sector */
		FLASH->CR &= CR_PSIZE_MASK;
		FLASH->CR |= voltageMask;
		FLASH->CR &= SECTOR_MASK;
		FLASH->CR |= FLASH_CR_SER | eraseSector;
		FLASH->CR |= FLASH_CR_STRT;

		/* Wait for last operation to be completed */
		status = flashStatus();

		/* if the erase operation is completed, disable the SER Bit */
		FLASH->CR &= (~FLASH_CR_SER);
		FLASH->CR &= SECTOR_MASK;

		flashLock();
		opDone = true;
	}else{
		opDone = false;
	}


	return opDone;
}


