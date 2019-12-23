/**
 * Name: gpio.cpp
 * Initial Author: andimoto
 */
#include <cstdint>
#include "gpio.hpp"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"


static GPIO_TypeDef* gpioBase[static_cast<std::uint8_t>(hal_uc::gpio::Port::PORT_ALL)] = {
		GPIOA,
		GPIOB,
		GPIOC,
		GPIOD,
		GPIOE,
		GPIOF,
		GPIOG,
		GPIOH,
		GPIOI,
		GPIOJ,
		GPIOK
};

static std::uint32_t gpioAhb[static_cast<std::uint8_t>(hal_uc::gpio::Port::PORT_ALL)] = {
		RCC_AHB1Periph_GPIOA,
		RCC_AHB1Periph_GPIOB,
		RCC_AHB1Periph_GPIOC,
		RCC_AHB1Periph_GPIOD,
		RCC_AHB1Periph_GPIOE,
		RCC_AHB1Periph_GPIOF,
		RCC_AHB1Periph_GPIOG,
		RCC_AHB1Periph_GPIOH,
		RCC_AHB1Periph_GPIOI,
		RCC_AHB1Periph_GPIOJ,
		RCC_AHB1Periph_GPIOK
};


hal_uc::gpio::gpioConfig::gpioConfig(const Port portConf, const Pin pinConf, const Mode modeConf,
		const Speed speedConf, const Type typeConf, const PushPull ppConf) :
		gpioPort(portConf), gpioPin(pinConf), gpioMode(modeConf),
		gpioSpeed(speedConf), gpioType(typeConf), gpioPushPull(ppConf)
{

}

static void initGpio(const hal_uc::gpio::gpioConfig& gpioInitConf)
{
	GPIO_InitTypeDef initPin;

	initPin.GPIO_Pin = static_cast<std::uint32_t>(gpioInitConf.gpioPin);
	initPin.GPIO_Mode = static_cast<GPIOMode_TypeDef>(gpioInitConf.gpioMode);
	initPin.GPIO_Speed = static_cast<GPIOSpeed_TypeDef>(gpioInitConf.gpioSpeed);
	initPin.GPIO_OType = static_cast<GPIOOType_TypeDef>(gpioInitConf.gpioType);
	initPin.GPIO_PuPd = static_cast<GPIOPuPd_TypeDef>(gpioInitConf.gpioPushPull);

	RCC_AHB1PeriphClockCmd(gpioAhb[static_cast<std::uint8_t>(gpioInitConf.gpioPort)], ENABLE);
	GPIO_Init(gpioBase[static_cast<std::uint8_t>(gpioInitConf.gpioPort)], &initPin);
}


hal_uc::gpio::gpio(const gpioConfig& gpioConfiguration) :
		gpioPort(gpioConfiguration.gpioPort),
		gpioPin(gpioConfiguration.gpioPin),
		gpioMode(gpioConfiguration.gpioMode)
{
	initGpio(gpioConfiguration);
}

void hal_uc::gpio::set(void)
{
	if(gpioMode == hal_uc::gpio::Mode::OUT)
	{
		GPIO_SetBits(gpioBase[static_cast<std::uint8_t>(gpioPort)], static_cast<std::uint16_t>(gpioPin));
	}
}

void hal_uc::gpio::reset(void)
{
	if(gpioMode == hal_uc::gpio::Mode::OUT)
	{
		GPIO_ResetBits(gpioBase[static_cast<std::uint8_t>(gpioPort)], static_cast<std::uint16_t>(gpioPin));
	}
}

void hal_uc::gpio::toggle(void)
{
	if(gpioMode == hal_uc::gpio::Mode::OUT)
	{
		GPIO_ToggleBits(gpioBase[static_cast<std::uint8_t>(gpioPort)], static_cast<std::uint16_t>(gpioPin));
	}
}

std::uint8_t hal_uc::gpio::get(void) const
{
	return static_cast<std::uint8_t>(
			GPIO_ReadInputDataBit(gpioBase[static_cast<std::uint8_t>(gpioPort)],
			static_cast<std::uint16_t>(gpioPin)));
}

