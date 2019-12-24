#include <cstdint>
#include <cstddef>
#include "gpio.hpp"


//const hal_uc::gpio::gpioConfig led_d1_conf(hal_uc::gpio::Port::PORT_H, hal_uc::gpio::Pin::PIN_2,
//		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
//		hal_uc::gpio::PushPull::NONE);

const hal_uc::gpio::gpioConfig led_d2_conf(hal_uc::gpio::Port::PORT_A, hal_uc::gpio::Pin::PIN_6,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);

const hal_uc::gpio::gpioConfig led_d3_conf(hal_uc::gpio::Port::PORT_A, hal_uc::gpio::Pin::PIN_7,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);

//const hal_uc::gpio::gpioConfig led_d4_conf(hal_uc::gpio::Port::PORT_I, hal_uc::gpio::Pin::PIN_10,
//		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
//		hal_uc::gpio::PushPull::NONE);

const hal_uc::gpio::gpioConfig user_k1_conf(hal_uc::gpio::Port::PORT_E, hal_uc::gpio::Pin::PIN_3,
		hal_uc::gpio::Mode::IN, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::UP);

const hal_uc::gpio::gpioConfig user_k0_conf(hal_uc::gpio::Port::PORT_E, hal_uc::gpio::Pin::PIN_4,
		hal_uc::gpio::Mode::IN, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::UP);

//static hal_uc::gpio* d1Ref = nullptr;
static hal_uc::gpio* d2Ref = nullptr;
static hal_uc::gpio* d3Ref = nullptr;
//static hal_uc::gpio* d4Ref = nullptr;

static hal_uc::gpio* k0Ref = nullptr;
static hal_uc::gpio* k1Ref = nullptr;

void initGpio(void)
{
//	static hal_uc::gpio led_d1(led_d1_conf);
	static hal_uc::gpio led_d2(led_d2_conf);
	static hal_uc::gpio led_d3(led_d3_conf);
//	static hal_uc::gpio led_d4(led_d4_conf);

	static hal_uc::gpio user_k0(user_k0_conf);
	static hal_uc::gpio user_k1(user_k1_conf);

//	d1Ref = &led_d1;
	d2Ref = &led_d2;
	d3Ref = &led_d3;
//	d4Ref = &led_d4;

	k0Ref = &user_k0;
	k1Ref = &user_k1;

//	led_d1.reset();
	led_d2.set();
	led_d3.reset();
//	led_d4.set();
}

void toggleLed(void)
{
//	d1Ref->toggle();
	d2Ref->toggle();
	d3Ref->toggle();
//	d4Ref->toggle();
}

std::uint8_t getButton(void)
{
	return k0Ref->get();
}




