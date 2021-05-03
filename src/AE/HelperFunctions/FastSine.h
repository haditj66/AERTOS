#pragma once

#ifdef SIMULATION
#include <cstdint>				  
#endif // SIMULATION

#include <math.h>
 
	 
namespace AE
{ 
	const float pi = 3.141592653589793f;
	const float Two_pi = pi * 2;
	const float half_pi = pi *.5f;
	const float threequarts_pi = pi * 1.5f;





	/// a fast sine approximation in radians using taylor series expansion as the approximation.
	static float sin(float x)
	{   

		//from 1.56 - pi/2 err = .0001475
		//from 1.55 - 1.56 err = .0001392
		//from 1.54 - 1.55 err = .0001315
		//from 1.53 - 1.54 err = .0001240
		//from 1.52 - 1.53 err = .0001170
		//from 1.5 - 1.52  err = .0001040
		//from 1.45 - 1.5  err = .00007665
		//from 1.4 - 1.45  err = .0000559 
		//from 1.35 - 1.4  err = .00004047
		//from 1.3 - 1.35  err = .00002879


		//from 1.25 - 1.3  err = -.0009258
		//from 1.2 - 1.25  err = -.0006970
		//from 1.15 - 1.2  err = -.0005182
		//from 1.1 - 1.15  err = -.0003802
		//from 1.05 - 1.1  err = -.0002750
		//from 1.0 - 1.05  err = -.0001957
		//from .9 -  1.00  err = -.00009376
		//from .7 -  .9    err = -.00001627


		//from .6 -  .7    err = .0006
		//from .5 -  .6    err = .0002589
		//from .4 -  .5    err = .000085
		//from  0 -  .4    err = 0


				float ans;
		float err; //the approimated error from the taylor series
		//float x_cubed = x*x*x;
		int8_t neg = 1;

		//negative quadrant; 
		if(x < 0)
		{ 
			if (isnan(x))
			{ 
				x = 0;
				//configASSERT(false)
			}

			return -1* AE::sin(abs(x));
		}

		//outside of quadrant 
		if(x >= Two_pi)
		{
//#pragma warning( disable : 4244)
			uint16_t div = (float)(x / (Two_pi));
			float newX = x - div * (Two_pi);
			return AE::sin(newX);
		}
		//quadrant 4
		else if(x >= (threequarts_pi))
		{
			neg = -1;
			x = Two_pi - x;
		}
		//quadrant 3
		else if(x >= (pi))
		{
			neg = -1;
			x = x - pi;
		}
		//quadrant 2
		else if(x >= (half_pi))
		{
			x = pi - x;
		}




		if (x <.7)
		{  
			float x_cubed = x * x*x;

			err = 0;
			x <.4 ? 0 :
			x <.5 ?.000085 :
			x <.6 ?.0002589 :
			x <.7 ?.0006 :
			0; 
			ans = x - (x_cubed / 6) + err;
		}
		else if (x > 1.3) 
		{
			float x_cubed = x * x*x;

			err = 
			x < 1.35 ?.00002879 :
			x < 1.4 ?.00004047 :
			x < 1.45 ?.0000559 :
			x < 1.5 ?.00007665 :
			//x < 1.52 ? .0001040 :
			//x < 1.53 ? .0001170 :
			//x < 1.54 ? .0001240 :
			//x < 1.55 ? .0001315 :
			x < 1.56 ?.0001392 :
			x < (half_pi) ?.0001475 :
			0;

			ans = x - (x_cubed / 6) + (x_cubed*x*x / 120) - (x_cubed*x_cubed*x / 5040) + err;
		}
		else 
		{
			float x_cubed = x * x*x;

			err = 0;
			x <.9 ? -.00001627 :
			x < 1  ? -.00009376 :
			x < 1.05 ? -.0001957 :
			x < 1.1 ? -.0002750 :
			x < 1.15 ? -.0003802 :
			x < 1.20 ? -.0005182 :
			x < 1.25 ? -.0006970 :
			0;

			ans = x - (x_cubed / 6) + (x_cubed*x*x / 120) + err;
		}

		ans = ans * neg;
		return ans;

	}


	static float cos(float x)
	{ 
		return sin(half_pi - x);
	}

}

 