#include "itm_write.h"
#include "rng.hpp"

extern void ramFunc(std::uint32_t num);

int main()
{
	unsigned int a = 0;
	std::uint32_t randomNumber = 0;
	bool error = true;

	hal_uc::rng rand1;

	rand1.start();

	for (;;)
	{
		a++;

		if(a==2000000)
		{
			a = 0;
			error = rand1.getNumber(randomNumber);
			if(error != true)
			{
				ramFunc(randomNumber);;
//				printf("Hallo %X\n", randomNumber);
			}
		}
	};

	return 0;
}
