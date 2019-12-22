#include <cstdint>
#include <cstddef>
#include "gpio.hpp"

const hal_uc::gpio::gpioConfig led_d2_conf(
		hal_uc::gpio::Port::PORT_A,
		hal_uc::gpio::Pin::PIN_6,
		hal_uc::gpio::Mode::OUT,
		hal_uc::gpio::Speed::FAST,
		hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::DOWN
);

const hal_uc::gpio::gpioConfig led_d3_conf(
		hal_uc::gpio::Port::PORT_A,
		hal_uc::gpio::Pin::PIN_7,
		hal_uc::gpio::Mode::OUT,
		hal_uc::gpio::Speed::FAST,
		hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::DOWN
);

static hal_uc::gpio* d2Ref = nullptr;
static hal_uc::gpio* d3Ref = nullptr;

void initGpio(void)
{
	static hal_uc::gpio led_d2(led_d2_conf);
	static hal_uc::gpio led_d3(led_d3_conf);

	d2Ref = &led_d2;
	d3Ref = &led_d3;

	led_d2.reset();
	led_d3.set();
}

void toggleLed(void)
{
	d2Ref->toggle();
	d3Ref->toggle();
}



