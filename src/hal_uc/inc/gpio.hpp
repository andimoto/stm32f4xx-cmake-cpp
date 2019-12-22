/**
 * Name: gpio.hpp
 * Initial Author: andimoto
 */
#include <cstdint>


namespace hal_uc
{


class gpio
{
public:
	enum class Port
	{
		PORT_A,
		PORT_B,
		PORT_C,
		PORT_D,
		PORT_E,
		PORT_F,
		PORT_G,
		PORT_H,
		PORT_I,
		PORT_J,
		PORT_K,
		PORT_ALL
	};

	enum class Pin
	{
		PIN_0 =	((uint16_t)0x0001),
		PIN_1 = ((uint16_t)0x0002),
		PIN_2 = ((uint16_t)0x0004),
		PIN_3 = ((uint16_t)0x0008),
		PIN_4 = ((uint16_t)0x0010),
		PIN_5 = ((uint16_t)0x0020),
		PIN_6 = ((uint16_t)0x0040),
		PIN_7 = ((uint16_t)0x0080),
		PIN_8 = ((uint16_t)0x0100),
		PIN_9 = ((uint16_t)0x0200),
		PIN_10 = ((uint16_t)0x0400),
		PIN_11 = ((uint16_t)0x0800),
		PIN_12 = ((uint16_t)0x1000),
		PIN_13 = ((uint16_t)0x2000),
		PIN_14 = ((uint16_t)0x4000),
		PIN_15 = ((uint16_t)0x8000),
		PIN_ALL = ((uint16_t)0xFFFF)
	};

	enum class Mode
	{
		IN = 0x00,
		OUT = 0x01,
		AF = 0x02,
		AN = 0x03
	};

	enum class Speed
	{
		LOW     = 0x00, /*!< Low speed    */
		MEDIUM  = 0x01, /*!< Medium speed */
		FAST    = 0x02, /*!< Fast speed   */
		HIGH    = 0x03  /*!< High speed   */
	};

	enum class Type
	{
		PUSHPULL,
		OPENDRAIN
	};

	enum class PushPull
	{
		NONE,
		UP,
		DOWN
	};

	struct gpioConfig
	{
	public:
		Port			gpioPort;
		Pin			    gpioPin;
		Mode 			gpioMode;
		Speed 			gpioSpeed;
		Type 			gpioType;
		PushPull		gpioPushPull;

		gpioConfig(const Port portConf, const Pin pinConf, const Mode modeConf,
				const Speed speedConf, const Type typeConf, const PushPull ppConf);
	};

	gpio(const gpioConfig& gpioConfiguration);

	void set(void);
	void reset(void);
	void toggle(void);

private:
	const Port gpioPort;
	const Pin gpioPin;
	const Mode gpioMode;
};


}
