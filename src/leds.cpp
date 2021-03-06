#include <cstdint>
#include <cstddef>
#include "gpio.hpp"


const hal_uc::gpio::gpioConfig led_d2_conf(hal_uc::gpio::Port::PORT_A, hal_uc::gpio::Pin::PIN_6,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);

const hal_uc::gpio::gpioConfig led_d3_conf(hal_uc::gpio::Port::PORT_A, hal_uc::gpio::Pin::PIN_7,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);

const hal_uc::gpio::gpioConfig user_k1_conf(hal_uc::gpio::Port::PORT_E, hal_uc::gpio::Pin::PIN_3,
		hal_uc::gpio::Mode::IN, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::UP);

const hal_uc::gpio::gpioConfig user_k0_conf(hal_uc::gpio::Port::PORT_E, hal_uc::gpio::Pin::PIN_4,
		hal_uc::gpio::Mode::IN, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::UP);

const hal_uc::gpio::gpioConfig user_kup_conf(hal_uc::gpio::Port::PORT_A, hal_uc::gpio::Pin::PIN_0,
		hal_uc::gpio::Mode::IN, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::DOWN);

static hal_uc::gpio* d2Ref = nullptr;
static hal_uc::gpio* d3Ref = nullptr;

static hal_uc::gpio* k0Ref = nullptr;
static hal_uc::gpio* k1Ref = nullptr;
static hal_uc::gpio* kupRef = nullptr;

void initGpio(void)
{
	static hal_uc::gpio led_d2(led_d2_conf);
	static hal_uc::gpio led_d3(led_d3_conf);

	static hal_uc::gpio user_k0(user_k0_conf);
	static hal_uc::gpio user_k1(user_k1_conf);
	static hal_uc::gpio user_kup(user_kup_conf);

	d2Ref = &led_d2;
	d3Ref = &led_d3;

	k0Ref = &user_k0;
	k1Ref = &user_k1;
	kupRef = &user_kup;

	led_d2.set();
	led_d3.reset();
}

void toggleLed(void)
{
	d2Ref->toggle();
	d3Ref->toggle();
}

std::uint8_t getButtonK0(void)
{
	return k0Ref->get();
}

std::uint8_t getButtonK1(void)
{
	return k1Ref->get();
}

std::uint8_t getButtonKUP(void)
{
	return kupRef->get();
}



