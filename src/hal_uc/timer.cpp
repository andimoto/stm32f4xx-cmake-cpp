/**
 * Name: timer.cpp
 * Initial Author: andimoto
 */

#include "timer.hpp"
#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "core_cm4.h"


static TIM_TypeDef* timers[static_cast<std::uint8_t>(hal_uc::timer::Instance::ALL)] = {
		TIM2,
		TIM3,
		TIM4,
		TIM5,
		TIM6,
		TIM7,
		TIM9,
		TIM10,
		TIM11,
		TIM12,
		TIM13,
		TIM14
};

static std::uint32_t rccTimers[static_cast<std::uint8_t>(hal_uc::timer::Instance::ALL)] = {
		RCC_APB1Periph_TIM2,
		RCC_APB1Periph_TIM3,
		RCC_APB1Periph_TIM4,
		RCC_APB1Periph_TIM5,
		RCC_APB1Periph_TIM6,
		RCC_APB1Periph_TIM7,
		RCC_APB2Periph_TIM9,
		RCC_APB2Periph_TIM10,
		RCC_APB2Periph_TIM11,
		RCC_APB1Periph_TIM13,
		RCC_APB1Periph_TIM14
};

static IRQn_Type nvicIrqMap[static_cast<std::uint8_t>(hal_uc::timer::Instance::ALL)] = {
		TIM2_IRQn,
		TIM3_IRQn,
		TIM4_IRQn,
		TIM5_IRQn,
		TIM6_DAC_IRQn,
		TIM7_IRQn,
		TIM1_BRK_TIM9_IRQn,
		TIM1_UP_TIM10_IRQn,
		TIM1_TRG_COM_TIM11_IRQn,
		TIM8_BRK_TIM12_IRQn,
		TIM8_UP_TIM13_IRQn
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
				const std::uint32_t periodConf, const ClockDiv clockDivConf, const std::uint8_t repetitionConf) :
		timInstance(instConf), prescaler(prescalerConf), counterMode(counterModeConf),
		period(periodConf), clockDiv(clockDivConf), repetitionCnt(repetitionConf)
{

}

static void initTimer(const hal_uc::timer::timConfig& timerConfigInit)
{
	TIM_TimeBaseInitTypeDef TimerBaseInit ;

	TimerBaseInit.TIM_Prescaler = static_cast<std::uint16_t>(timerConfigInit.prescaler);
	TimerBaseInit.TIM_CounterMode = static_cast<std::uint16_t>(timerConfigInit.counterMode);
	TimerBaseInit.TIM_Period = static_cast<std::uint32_t>(timerConfigInit.period);
	TimerBaseInit.TIM_ClockDivision = static_cast<std::uint16_t>(timerConfigInit.clockDiv);
	TimerBaseInit.TIM_RepetitionCounter = static_cast<std::uint16_t>(timerConfigInit.repetitionCnt);

	RCC_APB1PeriphClockCmd(rccTimers[static_cast<std::uint8_t>(timerConfigInit.timInstance)], ENABLE);
	TIM_TimeBaseInit(timers[static_cast<std::uint8_t>(timerConfigInit.timInstance)], &TimerBaseInit);
}

hal_uc::timer::timer(const timConfig timerConf, simplePointer timerIrqFuncConfig) :
		timInstance(timerConf.timInstance),
		timerIrqFunc(timerIrqFuncConfig)
{
	initTimer(timerConf);
}

std::uint32_t hal_uc::timer::get(void) const
{
	return static_cast<std::uint32_t>( timers[static_cast<std::uint8_t>(timInstance)]->CNT );
}

void hal_uc::timer::start(void)
{
	enableTimerIrq(timInstance); /* enable NVIC Irq */
	startTimerCtrl(timInstance); /* start timer */
}

void hal_uc::timer::stop(void)
{
	disableTimerIrq(timInstance); /* disable NVIC Irq */
	stopTimerCtrl(timInstance); /* stop timer */
}

void hal_uc::timer::irqHandler(void)
{
	/* call given irq function if not nullptr */
	if(timerIrqFunc != nullptr)
	{
		timerIrqFunc();
	}
}
