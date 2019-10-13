#pragma once
#include <iostream>
#include <iomanip>
#include <map>
#include <chrono>

#include "MyFunction.h"

class OptimalPassiveSearch: public MyFunction
	{
		long double top_edge;					     // Верхняя граница отрезка
		long double bottom_edge;					 // Нижняя граница отрезка
		long double delta;						     // Точность
		std::chrono::nanoseconds timer;	         // Время нахождения оптимального интервала
		public:

			
			// Обычный конструктор
			OptimalPassiveSearch(long double bottom, long double top, long double e = 0.1);

			~OptimalPassiveSearch()
			{}

			// Функция вычисляет погрешность
			double length_of_undefined_segment(int N);

			// Функция проводит все необходимые вычисления
			void pass();
	};