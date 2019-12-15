#include "itm_write.h"
#include "rng.hpp"

extern std::uint32_t ramFunc(std::uint32_t numA, std::uint32_t numB);
//extern std::uint32_t ramFuncCCM(std::uint32_t numA, std::uint32_t numB);

int main()
{
	unsigned int a = 0;
	std::uint32_t randomNumber = 0;
	std::uint32_t randomNumberA = 0;
	std::uint32_t randomNumberB = 0;
	bool error = true;

	hal_uc::rng rand1;


	rand1.start();

	for (;;)
	{
		a++;

		if(a==2000000)
		{
			a = 0;
			error = rand1.getNumber(randomNumberA);
			if(error != true)
				rand1.getNumber(randomNumberB);

			if(error != true)
			{
				randomNumber = ramFunc(randomNumberA, randomNumberB);
				printf("A %X\n", randomNumber);

//				randomNumber = ramFuncCCM(randomNumberA, randomNumberB);
//				printf("B %X\n", randomNumber);
			}
		}
	};

	return 0;
}
