#include <cstdint>
#include <cstddef>
#include "keyPad.hpp"

/* ---------------- ROW OUTPUTS ---------------- */
const hal_uc::gpio::gpioConfig row1_conf(hal_uc::gpio::Port::PORT_D, hal_uc::gpio::Pin::PIN_13,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);

const hal_uc::gpio::gpioConfig row2_conf(hal_uc::gpio::Port::PORT_D, hal_uc::gpio::Pin::PIN_12,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);

const hal_uc::gpio::gpioConfig row3_conf(hal_uc::gpio::Port::PORT_D, hal_uc::gpio::Pin::PIN_15,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);

const hal_uc::gpio::gpioConfig row4_conf(hal_uc::gpio::Port::PORT_D, hal_uc::gpio::Pin::PIN_14,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);

/* ---------------- COLUMN INPUTS ---------------- */
const hal_uc::gpio::gpioConfig col1_conf(hal_uc::gpio::Port::PORT_D, hal_uc::gpio::Pin::PIN_9,
		hal_uc::gpio::Mode::IN, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::DOWN);

const hal_uc::gpio::gpioConfig col2_conf(hal_uc::gpio::Port::PORT_D, hal_uc::gpio::Pin::PIN_8,
		hal_uc::gpio::Mode::IN, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::DOWN);

const hal_uc::gpio::gpioConfig col3_conf(hal_uc::gpio::Port::PORT_D, hal_uc::gpio::Pin::PIN_11,
		hal_uc::gpio::Mode::IN, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::DOWN);

const hal_uc::gpio::gpioConfig col4_conf(hal_uc::gpio::Port::PORT_D, hal_uc::gpio::Pin::PIN_10,
		hal_uc::gpio::Mode::IN, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::DOWN);

void progressKeyPad4x4(void)
{
	static std::uint8_t keyArray[4][4];

	static hal_pcb::keyPad4x4 keyPad4x4(row1_conf, row2_conf, row3_conf, row4_conf,
			col1_conf, col2_conf, col3_conf, col4_conf);

	std::uint8_t iRow, iCol = 0;

	keyPad4x4.scanKeyPad(keyArray);

	printf("\n\n\n");
	for(iRow = 0; iRow < 4; iRow++)
	{
		for(iCol = 0; iCol < 4; iCol++)
		{
			printf("%u ",keyArray[iCol][iRow]);
		}
		printf("\n");
	}

}
