#pragma once
#include <map>
#include <chrono>

#include "MyFunction.h"

class OptimalPassiveSearch: public MyFunction
	{
		long double  top_edge;			   // Верхняя граница отрезка
		long double  bottom_edge;		 	 // Нижняя граница отрезка
		long double  delta;			   	 	 // Точность
	 	unsigned int Value_N;					 //
		std::pair<long double, long double> point; // Конечная точка и интервал
		std::chrono::nanoseconds timer;	           // Время нахождения оптимального интервала
		public:


			// Обычный конструктор, принимает на вход нижнюю границу, верхнюю и точность
			OptimalPassiveSearch(long double bottom, long double top, long double accuracy = 0.05);

			~OptimalPassiveSearch()
			{}

			// Функция вычисляет погрешность
			double length_of_undefined_segment(int N);

			// Функция проводит все необходимые вычисления
			void pass();
			void pass2();
	};
