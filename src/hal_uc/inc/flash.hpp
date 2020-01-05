/**
 * Name: flash.hpp
 * Initial Author: andimoto
 */
#include <cstdint>

namespace hal_uc
{


class flash
{
public:
	enum class flashSector
	{
		FSECTOR_00, FSECTOR_01,	FSECTOR_02,	FSECTOR_03,	FSECTOR_04,	FSECTOR_05,
		FSECTOR_06,	FSECTOR_07,	FSECTOR_08,	FSECTOR_09,	FSECTOR_10,	FSECTOR_11,
		FSECTOR_12,	FSECTOR_13,	FSECTOR_14,	FSECTOR_15,	FSECTOR_16,	FSECTOR_17,
		FSECTOR_18,	FSECTOR_19,	FSECTOR_20,	FSECTOR_21,	FSECTOR_22,	FSECTOR_23,
		ALL_SECTORS
	};

	struct memConfig
	{
	public:
		const flashSector userSectorConfig;

		memConfig(const hal_uc::flash::flashSector sectorNo);
	};

	void printSectorConfig(void);

	std::uint32_t read(const std::uint32_t rdAddr);

	bool writeWord(const std::uint32_t wrAddr, const std::uint32_t wrData);

	std::uint8_t eraseSector(void);

	flash(const memConfig& sector);
private:
	bool checkAddress(const std::uint32_t checkAddress);

	const flashSector userSector;
	const std::uint32_t startAddress;
	const std::uint32_t sectorSize;
};

}
