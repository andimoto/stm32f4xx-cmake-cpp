/**
 * Name: timer.hpp
 * Initial Author: andimoto
 */
#ifndef HAL_UC_TIMER_H_
#define HAL_UC_TIMER_H_

#include <cstdint>
#include "types.hpp"

namespace hal_uc
{

class timer
{
public:
	enum class Instance
	{
		TIMER2,
		TIMER3,
		TIMER4,
		TIMER5,
		TIMER6,
		TIMER7,
		TIMER9,
		TIMER10,
		TIMER11,
		TIMER12,
		TIMER13,
		TIMER14,
		ALL
	};

	enum class CounterMode
	{
		UP = 0x0000,
		DOWN = 0x0010
	};

	enum class ClockDiv
	{
		DIV1 = 0x0000,
		DIV2 = 0x0100,
		DIV4 = 0x0200
	};

	struct timConfig
	{
		const Instance timInstance;
		const std::uint16_t prescaler;
		const CounterMode counterMode;
		const std::uint32_t period;
		const ClockDiv clockDiv;
		const std::uint8_t repetitionCnt;

		timConfig(const Instance instConf, const std::uint16_t prescalerConf, const CounterMode counterModeConf,
				const std::uint32_t periodConf, const ClockDiv clockDivConf, const std::uint8_t repetitionConf);
	};

	void start(void);

	void stop(void);

	std::uint32_t get(void) const;

	void irqHandler(void);

	timer(const timConfig timerConf, const simplePointer timerIrqFuncConfig = nullptr);

private:
	const Instance timInstance;
	const simplePointer timerIrqFunc;


};

}

#endif /* HAL_UC_TIMER_H_ */
