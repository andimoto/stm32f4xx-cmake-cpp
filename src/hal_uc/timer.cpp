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
		RCC_APB1Periph_TIM12,
		RCC_APB1Periph_TIM13,
		RCC_APB1Periph_TIM14
};

typedef enum periphBus
{
	APB1,
	APB2
};

static std::uint32_t apbOfTimers[static_cast<std::uint8_t>(hal_uc::timer::Instance::ALL)] = {
		APB1,
		APB1,
		APB1,
		APB1,
		APB1,
		APB1,
		APB2,
		APB2,
		APB2,
		APB1,
		APB1,
		APB1
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
		TIM8_UP_TIM13_IRQn,
		TIM8_TRG_COM_TIM14_IRQn
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

static void registerTimerObject(hal_uc::timer* timerObj, const hal_uc::timer::Instance timerObjInstance);

static void initTimer(const hal_uc::timer::timConfig& timerConfigInit)
{
	TIM_TimeBaseInitTypeDef TimerBaseInit ;

	TimerBaseInit.TIM_Prescaler = static_cast<std::uint16_t>(timerConfigInit.prescaler);
	TimerBaseInit.TIM_CounterMode = static_cast<std::uint16_t>(timerConfigInit.counterMode);
	TimerBaseInit.TIM_Period = static_cast<std::uint32_t>(timerConfigInit.period);
	TimerBaseInit.TIM_ClockDivision = static_cast<std::uint16_t>(timerConfigInit.clockDiv);
	TimerBaseInit.TIM_RepetitionCounter = static_cast<std::uint16_t>(timerConfigInit.repetitionCnt);

	if(apbOfTimers[static_cast<std::uint8_t>(timerConfigInit.timInstance)] == APB1)
	{
		RCC_APB1PeriphClockCmd(rccTimers[static_cast<std::uint8_t>(timerConfigInit.timInstance)], ENABLE);
	}else{
		RCC_APB2PeriphClockCmd(rccTimers[static_cast<std::uint8_t>(timerConfigInit.timInstance)], ENABLE);
	}
	TIM_TimeBaseInit(timers[static_cast<std::uint8_t>(timerConfigInit.timInstance)], &TimerBaseInit);
}

hal_uc::timer::timer(const timConfig timerConf, simplePointer timerIrqFuncConfig) :
		timInstance(timerConf.timInstance),
		timerIrqFunc(timerIrqFuncConfig)
{
	initTimer(timerConf);
	/* register this timer object for usage in TIMx_IRQHandler */
	registerTimerObject(this, timInstance);
}

std::uint32_t hal_uc::timer::get(void) const
{
	return static_cast<std::uint32_t>( timers[static_cast<std::uint8_t>(timInstance)]->CNT );
}

void hal_uc::timer::start(void)
{
	/* enable irq only if an irq handler function has been provided */
	if(timerIrqFunc != nullptr)
	{
		enableTimerIrq(timInstance); /* enable NVIC Irq */
	}
	startTimerCtrl(timInstance); /* start timer */
}

void hal_uc::timer::stop(void)
{
	/* enable irq only if an irq handler function has been provided */
	if(timerIrqFunc != nullptr)
	{
		disableTimerIrq(timInstance); /* disable NVIC Irq */
	}
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


/*******************************/
/* * * * * IRQ Handler * * * * */
/*******************************/

/* timer object pointers for using in TIMx_IRQ_Handler functions */
static hal_uc::timer* tim2ref = nullptr;
static hal_uc::timer* tim3ref = nullptr;
static hal_uc::timer* tim4ref = nullptr;
static hal_uc::timer* tim5ref = nullptr;
static hal_uc::timer* tim6ref = nullptr;
static hal_uc::timer* tim7ref = nullptr;
static hal_uc::timer* tim9ref = nullptr;
static hal_uc::timer* tim10ref = nullptr;
static hal_uc::timer* tim11ref = nullptr;
static hal_uc::timer* tim12ref = nullptr;
static hal_uc::timer* tim13ref = nullptr;
static hal_uc::timer* tim14ref = nullptr;


static void registerTimerObject(hal_uc::timer* timerObj, const hal_uc::timer::Instance timerObjInstance)
{
	switch(timerObjInstance)
	{
	case hal_uc::timer::Instance::TIMER2: tim2ref = timerObj; break;
	case hal_uc::timer::Instance::TIMER3: tim3ref = timerObj; break;
	case hal_uc::timer::Instance::TIMER4: tim4ref = timerObj; break;
	case hal_uc::timer::Instance::TIMER5: tim5ref = timerObj; break;
	case hal_uc::timer::Instance::TIMER6: tim6ref = timerObj; break;
	case hal_uc::timer::Instance::TIMER7: tim7ref = timerObj; break;
	case hal_uc::timer::Instance::TIMER9: tim9ref = timerObj; break;
	case hal_uc::timer::Instance::TIMER10: tim10ref = timerObj; break;
	case hal_uc::timer::Instance::TIMER11: tim11ref = timerObj; break;
	case hal_uc::timer::Instance::TIMER12: tim12ref = timerObj; break;
	case hal_uc::timer::Instance::TIMER13: tim13ref = timerObj; break;
	case hal_uc::timer::Instance::TIMER14: tim14ref = timerObj; break;
	case hal_uc::timer::Instance::ALL:
		while(1){
			/* fail config! run into endless loop */
		};
		break;
	}
}

extern "C" void TIM2_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // @suppress("Invalid arguments")
	if(tim2ref != nullptr)
	{
		tim2ref->irqHandler();
	}
}

extern "C" void TIM3_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	if(tim3ref != nullptr)
	{
		tim3ref->irqHandler();
	}
}

extern "C" void TIM4_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	if(tim4ref != nullptr)
	{
		tim4ref->irqHandler();
	}
}

extern "C" void TIM5_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	if(tim5ref != nullptr)
	{
		tim5ref->irqHandler();
	}
}

extern "C" void TIM6_DAC_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update); // @suppress("Invalid arguments")
	if(tim6ref != nullptr)
	{
		tim6ref->irqHandler();
	}
}


extern "C" void TIM7_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	if(tim7ref != nullptr)
	{
		tim7ref->irqHandler();
	}
}


extern "C" void TIM1_BRK_TIM9_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
	if(tim9ref != nullptr)
	{
		tim9ref->irqHandler();
	}
}


extern "C" void TIM1_UP_TIM10_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM10, TIM_IT_Update);
	if(tim10ref != nullptr)
	{
		tim10ref->irqHandler();
	}
}

extern "C" void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM11, TIM_IT_Update);
	if(tim11ref != nullptr)
	{
		tim11ref->irqHandler();
	}
}

extern "C" void TIM8_BRK_TIM12_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM12, TIM_IT_Update);
	if(tim12ref != nullptr)
	{
		tim12ref->irqHandler();
	}
}

extern "C" void TIM8_UP_TIM13_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM13, TIM_IT_Update);
	if(tim13ref != nullptr)
	{
		tim13ref->irqHandler();
	}
}

extern "C" void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM14, TIM_IT_Update);
	if(tim14ref != nullptr)
	{
		tim14ref->irqHandler();
	}
}



