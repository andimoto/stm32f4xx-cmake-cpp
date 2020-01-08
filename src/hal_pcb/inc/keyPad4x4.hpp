/**
 * Name: keyPad4x4.hpp
 * Initial Author: andimoto
 */
#ifndef HAL_PCB_KEYPAD4X4_H_
#define HAL_PCB_KEYPAD4X4_H_

#include <cstdint>
#include <cstddef>
#include "gpio.hpp"

namespace hal_pcb
{

class keyPad4x4
{
public:
	void scanKeyPad(std::uint8_t keyArray[4][4]);

	keyPad4x4(const hal_uc::gpio::gpioConfig& row1Conf, const hal_uc::gpio::gpioConfig& row2Conf,
			const hal_uc::gpio::gpioConfig& row3Conf, const hal_uc::gpio::gpioConfig& row4Conf,
			const hal_uc::gpio::gpioConfig& col1Conf, const hal_uc::gpio::gpioConfig& col2Conf,
			const hal_uc::gpio::gpioConfig& col3Conf, const hal_uc::gpio::gpioConfig& col4Conf);
private:
	hal_uc::gpio *row[4];
	hal_uc::gpio *col[4];
};

}

#endif /* HAL_PCB_KEYPAD4X4_H_ */
