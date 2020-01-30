#include <cstdint>
#include <cstddef>
#include "gpio.hpp"


const hal_uc::gpio::gpioConfig lcd_din_conf(hal_uc::gpio::Port::PORT_C, hal_uc::gpio::Pin::PIN_3,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);

const hal_uc::gpio::gpioConfig lcd_clk_conf(hal_uc::gpio::Port::PORT_B, hal_uc::gpio::Pin::PIN_10,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);

const hal_uc::gpio::gpioConfig lcd_cs_conf(hal_uc::gpio::Port::PORT_B, hal_uc::gpio::Pin::PIN_11,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::UP);

const hal_uc::gpio::gpioConfig lcd_dc_conf(hal_uc::gpio::Port::PORT_C, hal_uc::gpio::Pin::PIN_0,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::UP);

const hal_uc::gpio::gpioConfig lcd_res_conf(hal_uc::gpio::Port::PORT_C, hal_uc::gpio::Pin::PIN_1,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::UP);

void runLCD(void)
{
	static hal_uc::gpio lcd_din(lcd_din_conf);
	static hal_uc::gpio lcd_clk(lcd_clk_conf);

	static hal_uc::gpio lcd_cs(lcd_cs_conf);
	static hal_uc::gpio lcd_dc(lcd_dc_conf);
	static hal_uc::gpio lcd_res(lcd_res_conf);

	lcd_clk.set();
	lcd_din.set();
	lcd_cs.set();
	lcd_dc.set();

}
