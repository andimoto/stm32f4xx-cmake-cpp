/**
 * Name: gpio.cpp
 * Initial Author: andimoto
 */
#include <cstdint>
#include "gpio.hpp"
#include "stm32f4xx_gpio.h"

hal_uc::gpio::gpioConfig::gpioConfig(const Port portConf, const Pin pinConf, const Mode modeConf,
		const Speed speedConf, const Type typeConf, const PushPull ppConf) :
		gpioPort(portConf), gpioPin(pinConf), gpioMode(modeConf),
		gpioSpeed(speedConf), gpioType(typeConf), gpioPushPull(ppConf)
{

}

hal_uc::gpio::gpio(const gpioConfig& gpioConfiguration) :
		gpioPort(gpioConfiguration.gpioPort),
		gpioPin(gpioConfiguration.gpioPin)
{

}
