/**
 * Name: timer.cpp
 * Initial Author: andimoto
 */

#include "timer.hpp"
#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "core_cm4.h"


static TIM_TypeDef* timers[static_cast<std::uint8_t>(hal_uc::timer::Instance::ALL)] = {
		 TIM2
};

static std::uint32_t rccTimers[static_cast<std::uint8_t>(hal_uc::timer::Instance::ALL)] = {
		RCC_APB1Periph_TIM2
};

static IRQn_Type nvicIrqMap[static_cast<std::uint8_t>(hal_uc::timer::Instance::ALL)] = {
		TIM2_IRQn
};

static void startTimerCtrl(const hal_uc::timer::Instance tim)
{
	timers[static_cast<std::uint8_t>(tim)]->CR1 |= static_cast<std::uint16_t>(TIM_CR1_CEN);
}

static void stopTimerCtrl(const hal_uc::timer::Instance tim)
{
	timers[static_cast<std::uint8_t>(tim)]->CR1 = static_cast<std::uint16_t>(~TIM_CR1_CEN);
}

static void enableTimerIrq(const hal_uc::timer::Instance tim)
{
	timers[static_cast<std::uint8_t>(tim)]->DIER |= static_cast<std::uint16_t>(TIM_IT_Update);
	NVIC_EnableIRQ(nvicIrqMap[static_cast<std::uint8_t>(tim)]);
}

static void disableTimerIrq(const hal_uc::timer::Instance tim)
{
	timers[static_cast<std::uint8_t>(tim)]->DIER = static_cast<std::uint16_t>(~TIM_IT_Update);
	NVIC_DisableIRQ(nvicIrqMap[static_cast<std::uint8_t>(tim)]);
}


hal_uc::timer::timConfig::timConfig(const Instance instConf, const std::uint16_t prescalerConf, const CounterMode counterModeConf,
				const std::uint32_t periodConf, const ClockDiv clockDivConf, const std::uint8_t repetitionConf,
				const bool irqOnConf) :
		timInstance(instConf), prescaler(prescalerConf), counterMode(counterModeConf),
		period(periodConf), clockDiv(clockDivConf), repetitionCnt(repetitionConf), irqOn(irqOnConf)
{

}



hal_uc::timer::timer(const timConfig timerConf) :
		timInstance(timerConf.timInstance),
		useIrq(timerConf.irqOn)
{
	TIM_TimeBaseInitTypeDef TimerBaseInit ;

	TimerBaseInit.TIM_Prescaler = static_cast<std::uint16_t>(timerConf.prescaler);
	TimerBaseInit.TIM_CounterMode = static_cast<std::uint16_t>(timerConf.counterMode);
	TimerBaseInit.TIM_Period = static_cast<std::uint32_t>(timerConf.period);
	TimerBaseInit.TIM_ClockDivision = static_cast<std::uint16_t>(timerConf.clockDiv);
	TimerBaseInit.TIM_RepetitionCounter = static_cast<std::uint16_t>(timerConf.repetitionCnt);

	RCC_APB1PeriphClockCmd(rccTimers[static_cast<std::uint8_t>(timInstance)], ENABLE);
	TIM_TimeBaseInit(timers[static_cast<std::uint8_t>(timInstance)], &TimerBaseInit);
}

std::uint32_t hal_uc::timer::get(void) const
{
	return static_cast<std::uint32_t>( timers[static_cast<std::uint8_t>(timInstance)]->CNT );
}

void hal_uc::timer::start(void)
{
	if(useIrq)
	{
		enableTimerIrq(timInstance);
	}
	startTimerCtrl(timInstance);
}

void hal_uc::timer::stop(void)
{
	if(useIrq)
	{
		disableTimerIrq(timInstance);
	}
	stopTimerCtrl(timInstance);
}

void hal_uc::timer::irqHandler(void)
{

}
