#include <cstdint>
#include <cstddef>
#include "keyPad4x4.hpp"

hal_pcb::keyPad4x4::keyPad4x4(const hal_uc::gpio::gpioConfig& row1Conf, const hal_uc::gpio::gpioConfig& row2Conf,
		const hal_uc::gpio::gpioConfig& row3Conf, const hal_uc::gpio::gpioConfig& row4Conf,
		const hal_uc::gpio::gpioConfig& col1Conf, const hal_uc::gpio::gpioConfig& col2Conf,
		const hal_uc::gpio::gpioConfig& col3Conf, const hal_uc::gpio::gpioConfig& col4Conf)
{
	static hal_uc::gpio r1(row1Conf);
	row[0] = &r1;
	static hal_uc::gpio r2(row2Conf);
	row[1] = &r2;
	static hal_uc::gpio r3(row3Conf);
	row[2] = &r3;
	static hal_uc::gpio r4(row4Conf);
	row[3] = &r4;

	static hal_uc::gpio c1(col1Conf);
	col[0] = &c1;
	static hal_uc::gpio c2(col2Conf);
	col[1] = &c2;
	static hal_uc::gpio c3(col3Conf);
	col[2] = &c3;
	static hal_uc::gpio c4(col4Conf);
	col[3] = &c4;
}


void hal_pcb::keyPad4x4::scanKeyPad(std::uint8_t keyArray[4][4])
{
	std::uint8_t iRow = 0;
	std::uint8_t iCol = 0;

	for(iCol = 0; iCol < 4; iCol++)
	{
		row[iCol]->set();
		for(iRow = 0; iRow < 4; iRow++)
		{
			keyArray[iCol][iRow] = col[iRow]->get();
		}
		row[iCol]->reset();
	}

}
