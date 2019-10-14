#pragma once
#include <iostream>
#include <map>
#include <chrono>

#include "MyFunction.h"

class GoldrenSection: public MyFunction
	{
		long double top_edge;					 	 // Верхняя граница отрезка
		long double bottom_edge;			 	 // Нижняя граница отрезка
		long double delta;					 	   // Точность
		std::chrono::nanoseconds timer; // Время нахождения оптимального интервала
		long double interval;					 	 // Длина интервала

		std::pair<long double, long double> first_point;	 // точка 1 / значение 1
		std::pair<long double, long double> second_point;	 // точка 2 / значение 2

		const long double t = (1.0 + sqrt(5)) / 2.0;
	public:

		// Обычный конструктор
		GoldrenSection(long double bottom, long double top, long double accuracy = 0.05);

		~GoldrenSection()
			{}

		void update_interval();

		/*Функция обновления первой точки
		   Если она пустая, то обновляем её, если нет,
		   то занчит нужно поменять 1 и 2 точки местами*/
		void update_point1();
		/*Функция обновления второй точки
		   Если она пустая, то обновляем её, если нет,
		   то занчит нужно поменять 2 и 1 точки местами*/
		void update_point2();

		// Методы возвращают true если точка 1 или 2  - пустые полностью. Иначе false.
		bool point1_empty()
			{
				return (first_point.first == 0.0) && (first_point.second == 0.0);
			}
		bool point2_empty()
			{
				return (second_point.first == 0.0) && (second_point.second == 0.0);
			}

		// Функция проводит все необходимые вычисления
		void pass();
	};
