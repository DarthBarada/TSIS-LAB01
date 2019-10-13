#include <iostream>
#include "OptimalPassiveSearch.h"
#include "GoldrenSection.h"

int main()
	{
		OptimalPassiveSearch a(2, 6);
		a.pass();
		GoldrenSection b(2, 6);
		b.pass();
	}
