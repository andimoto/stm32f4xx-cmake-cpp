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
	struct memConfig
	{
	public:
		std::uint32_t startAddr;
		std::uint32_t secSize;

		memConfig(const std::uint32_t startAddrConf, const std::uint32_t secSizeConf);
	};

	void getConfig(void);

	flash(const memConfig& sector);
private:
	const std::uint32_t startAddress;
	const std::uint32_t sectorSize;
};

}
