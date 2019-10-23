#pragma once
#include <map>
#include <chrono>

#include "MyFunction.h"

class OptimalPassiveSearch: public MyFunction
	{
		double  top_edge;			   // Верхняя граница отрезка
		double  bottom_edge;		 	 // Нижняя граница отрезка
		double  delta;			   	 	 // Точность
	 	unsigned int Value_N;					 //
		std::pair<double,double> point; // Конечная точка и её значение
		std::chrono::nanoseconds timer;	           // Время нахождения оптимального интервала
		public:


			// Обычный конструктор, принимает на вход нижнюю границу, верхнюю и точность
			OptimalPassiveSearch(double bottom, double top, double accuracy = 0.05);

			~OptimalPassiveSearch() = default; 

			// Функция вычисляет погрешность
			double length_of_undefined_segment(int N);

			// Функция проводит все необходимые вычисления
			void pass();
			void test_pass();
	};
