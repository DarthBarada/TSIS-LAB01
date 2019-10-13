#pragma once
#include <cmath>

class MyFunction
	{
		public:
			long double F(long double x)
				{
					return (-2.0)*sqrt(x)*sin(0.5*x);
				}
	};