/**
 * Name: rng.hpp
 * Initial Author: andimoto
 */
#ifndef HAL_UC_RNG_H_
#define HAL_UC_RNG_H_

#include <cstdint>
#include <cstddef>

namespace hal_uc
{

/**
 * Random Number Generator class
 * */

class rng
{
public:
	bool getNumber(std::uint32_t& randNo);
	void start(void);
	void stop(void);

	rng();
private:
	bool isStopped = true;
};

}

#endif /* HAL_UC_RNG_H_ */
