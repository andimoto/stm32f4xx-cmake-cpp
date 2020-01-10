/**
 * Name: keyPad.hpp
 * Initial Author: andimoto
 */
#include <cstdint>
#include <cstddef>
#include "keyPad.hpp"
#include "led8Array.hpp"

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

/* ---------------- LEDARRAY OUTPUTS ---------------- */
const hal_uc::gpio::gpioConfig d1_conf(hal_uc::gpio::Port::PORT_D, hal_uc::gpio::Pin::PIN_0,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);

const hal_uc::gpio::gpioConfig d2_conf(hal_uc::gpio::Port::PORT_D, hal_uc::gpio::Pin::PIN_1,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);

const hal_uc::gpio::gpioConfig d3_conf(hal_uc::gpio::Port::PORT_D, hal_uc::gpio::Pin::PIN_2,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);

const hal_uc::gpio::gpioConfig d4_conf(hal_uc::gpio::Port::PORT_D, hal_uc::gpio::Pin::PIN_3,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);

const hal_uc::gpio::gpioConfig d5_conf(hal_uc::gpio::Port::PORT_D, hal_uc::gpio::Pin::PIN_4,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);

const hal_uc::gpio::gpioConfig d6_conf(hal_uc::gpio::Port::PORT_D, hal_uc::gpio::Pin::PIN_5,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);

const hal_uc::gpio::gpioConfig d7_conf(hal_uc::gpio::Port::PORT_D, hal_uc::gpio::Pin::PIN_6,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);

const hal_uc::gpio::gpioConfig d8_conf(hal_uc::gpio::Port::PORT_D, hal_uc::gpio::Pin::PIN_7,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::NONE);


void printArray4x4(std::uint8_t keyArray[4][4])
{
	printf("\n\n");
	for(std::uint8_t iRow = 0; iRow < 4; iRow++)
	{
		for(std::uint8_t iCol = 0; iCol < 4; iCol++)
		{
			printf("%u ",keyArray[iCol][iRow]);
		}
		printf("\n");
	}
}

void progressKeyPad4x4(void)
{
	bool printArray = false;
	static std::uint8_t keyArray[4][4];

	static hal_pcb::keyPad4x4 keyPad4x4(row1_conf, row2_conf, row3_conf, row4_conf,
			col1_conf, col2_conf, col3_conf, col4_conf);

	static hal_pcb::led8Array ledArray(d1_conf,d2_conf,d3_conf,d4_conf,
			d5_conf,d6_conf,d7_conf,d8_conf);

	std::uint8_t iRow, iCol = 0;

	keyPad4x4.scanKeyPad(keyArray);


	for(iRow = 0; iRow < 4; iRow++)
	{
		for(iCol = 0; iCol < 4; iCol++)
		{
			if(keyArray[iCol][iRow] == 1)
			{
				printArray = true;
			}
		}
	}
	if(printArray)
		printArray4x4(keyArray);

	if(keyArray[1][1])
	{
		ledArray.setLed(hal_pcb::led8Array::ledNum::ALL);
	}
	if(keyArray[3][1])
	{
		ledArray.turnOff();
	}
	else{
		ledArray.runMode();
	}
}
