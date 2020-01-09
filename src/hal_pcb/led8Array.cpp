/**
 * Name: led8Array.cpp
 * Initial Author: andimoto
 */
#include <cstdint>
#include <cstddef>
#include "led8Array.hpp"

hal_pcb::led8Array::led8Array(const hal_uc::gpio::gpioConfig& led1Conf, const hal_uc::gpio::gpioConfig& led2Conf,
		const hal_uc::gpio::gpioConfig& led3Conf, const hal_uc::gpio::gpioConfig& led4Conf,
		const hal_uc::gpio::gpioConfig& led5Conf, const hal_uc::gpio::gpioConfig& led6Conf,
		const hal_uc::gpio::gpioConfig& led7Conf, const hal_uc::gpio::gpioConfig& led8Conf) :
		ledArrayMode(hal_pcb::led8Array::mode::RUN), currentMask(0)
{
	static hal_uc::gpio d1(led1Conf);
	led[0] = &d1;
	static hal_uc::gpio d2(led2Conf);
	led[1] = &d2;
	static hal_uc::gpio d3(led3Conf);
	led[2] = &d3;
	static hal_uc::gpio d4(led4Conf);
	led[3] = &d4;

	static hal_uc::gpio d5(led5Conf);
	led[5] = &d5;
	static hal_uc::gpio d6(led6Conf);
	led[6] = &d6;
	static hal_uc::gpio d7(led7Conf);
	led[7] = &d7;
	static hal_uc::gpio d8(led8Conf);
	led[8] = &d8;
}

void hal_pcb::led8Array::setMask(const std::uint8_t ledMask)
{
	std::uint8_t index = 0;
	std::uint8_t temp = 0;

	for(index = 0; index < 8; index++)
	{
		temp = (currentMask >> index) & 0x01;
		if(!temp)
		{
			led[index]->set();
		}else{
			led[index]->reset();
		}
	}
	currentMask = ledMask;
}

std::uint8_t hal_pcb::led8Array::readMask(void) const
{
	return currentMask;
}

void hal_pcb::led8Array::turnOff(void)
{
	ledArrayMode = mode::STATIC;
	currentMask = 0;
	setMask(currentMask);
}

void hal_pcb::led8Array::setLed(const ledNum ledNo)
{
	ledArrayMode = mode::STATIC;
	if(ledNo == ledNum::ALL)
	{
		currentMask = 0xFF;
	}else{
		std::uint8_t temp = 0x01 << static_cast<std::uint8_t>(ledNo);
		currentMask |= temp;
	}
	setMask(currentMask);
}

void hal_pcb::led8Array::resetLed(const ledNum ledNo)
{
	ledArrayMode = mode::STATIC;
	std::uint8_t temp = 0x01 << static_cast<std::uint8_t>(ledNo);
	currentMask &= temp;
	setMask(currentMask);
}

void hal_pcb::led8Array::runMode(void)
{
	static std::uint8_t runMask = 0x01;
	static bool leftDirection = true;
	ledArrayMode = mode::RUN;

	setMask(runMask);

	if(leftDirection == true)
	{
		runMask = runMask << 1;
		if(runMask == 0x80)
			leftDirection = false;
	}else{
		runMask = runMask >> 1;
		if(runMask == 0x01)
			leftDirection = true;
	}
}
