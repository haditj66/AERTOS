#include <random>
#include <time.h>
class AE_rand
{
	friend void  AEInit();
	

	static std::default_random_engine generator;
public:
	//only do this once.
	static void init_QRrand()
	{
		//seed it with the current time.
		srand(time(0));
		 
	}


	static uint64_t getRandom_uint64(uint64_t const& min = 0, uint64_t const& max = 0xffffffffffffffff)
	{
		return (((uint64_t)(unsigned int)rand() << 32) + (uint64_t)(unsigned int)rand()) % (max - min) + min;

	}

	static uint32_t getRandom_uint32(uint32_t const& min = 0, uint32_t const& max = 0xffffffff)
	{
		return (uint32_t)rand() % (max - min) + min;

	}
	
	static float getRandomGaussianDistribution(float mean, float standardDeviation)
	{
		
		std::normal_distribution<float> distribution( mean,  standardDeviation);

		float randomNumber = distribution(generator);
	}

};