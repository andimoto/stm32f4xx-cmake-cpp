/**
 * Name: led8Array.hpp
 * Initial Author: andimoto
 */
#ifndef HAL_PCB_LED8_ARRAY_H_
#define HAL_PCB_LED8_ARRAY_H_

#include <cstdint>
#include <cstddef>
#include "gpio.hpp"

namespace hal_pcb
{
class led8Array
{
public:
	enum class mode
	{
		STATIC,
		RUN
	};

	enum class ledNum
	{
		D1,
		D2,
		D3,
		D4,
		D5,
		D6,
		D7,
		D8,
		ALL
	};

	void turnOff(void);

	void runMode(void);
	void setMask(const std::uint8_t ledMask);
	void setLed(const ledNum ledNo);
	void resetLed(const ledNum ledNo);

	std::uint8_t readMask(void) const;

	led8Array(const hal_uc::gpio::gpioConfig& led1Conf, const hal_uc::gpio::gpioConfig& led2Conf,
			const hal_uc::gpio::gpioConfig& led3Conf, const hal_uc::gpio::gpioConfig& led4Conf,
			const hal_uc::gpio::gpioConfig& led5Conf, const hal_uc::gpio::gpioConfig& led6Conf,
			const hal_uc::gpio::gpioConfig& led7Conf, const hal_uc::gpio::gpioConfig& led8Conf);

private:
	hal_uc::gpio *led[8];
	mode ledArrayMode;
	std::uint8_t currentMask;
};
}

#endif /* HAL_PCB_LED8_ARRAY_H_ */
