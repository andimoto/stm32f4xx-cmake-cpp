/**
 * Name: rng.cpp
 * Initial Author: andimoto
 */
#include "rng.hpp"
#include "stm32f4xx.h"
#include "stm32f4xx_rng.h"


hal_uc::rng::rng(void)
{
	/*
	 * Enable RNG Module
	 * */
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
}

bool hal_uc::rng::getNumber(std::uint32_t& randNo)
{
	if(!isStopped && (RNG_GetFlagStatus(RNG_FLAG_DRDY) == SET))
	{
		randNo = static_cast<std::uint32_t>(RNG_GetRandomNumber());
	}
	return isStopped;
}

void hal_uc::rng::start(void)
{
	/* start rng module by enable generating numbers */
	RNG_Cmd(ENABLE);
	isStopped = false;
}

void hal_uc::rng::stop(void)
{
	/* stop rng module by disabling generating numbers */
	RNG_Cmd(DISABLE);
	isStopped = true;
}
