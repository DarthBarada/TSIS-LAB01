#include "GoldrenSection.h"

GoldrenSection::GoldrenSection()
	{
		top_edge = 0.0;
		bottom_edge = 0.0;
		delta = 0.0;
	}

GoldrenSection::GoldrenSection(long double bottom, long double top, long double e)
	{
		top_edge = top; bottom_edge = bottom; delta = e;
		interval = top - bottom;

		//		Подготовка 2 точек к 1 шагу
		long double dot = 0;
		dot = bottom_edge + (1 - 1 / t)*top_edge;
		first_point = std::make_pair(dot, F(dot));

		dot = bottom_edge + top_edge / t;
		second_point = std::make_pair(dot, F(dot));
		//				-----------
	}

void GoldrenSection::update_interval()
	{
		interval = top_edge - bottom_edge;
	}

void GoldrenSection::update_point1()
	{
		if (first_point.first == 0.0 && first_point.second == 0.0)
			{
				long double dot1 = bottom_edge + top_edge - second_point.first;
				first_point = std::make_pair(dot1, F(dot1));
			}
		else
			{
				top_edge = second_point.first;
				second_point = first_point;
				first_point = std::make_pair(0.0, 0.0);
				update_interval();
			}
	}

void GoldrenSection::update_point2()
	{
		if (second_point.first == 0.0 && second_point.second == 0.0)
			{
				long double dot2 = bottom_edge + top_edge - first_point.first;
				second_point = std::make_pair(dot2, F(dot2));
			}
		else
			{
				bottom_edge = first_point.first;
				first_point = second_point;
				second_point = std::make_pair(0.0, 0.0);
				update_interval();
			}
	}

void GoldrenSection::pass()
	{
		setlocale(LC_ALL, "RU");
		std::cout <<std::left<<"\nМетод золотого сечения\n"
			<< "_______________________________________________________\n"
			<< std::setw(13) << "" << "|" << std::setw(10) << "Длина" << "||" << std::setw(6) << "" << "|" << std::setw(6) << "" << "||" << std::setw(6) << "" << "|" << std::setw(6) << "" << "|\n"
			<< std::setw(13) << "Интервал" << "|" << std::setw(10) << "интервала" << "||" << std::setw(6) << "X1" << "|" << std::setw(6) << "X2" << "||" << std::setw(6) << "F(X1)" << "|" << std::setw(6) << "F(X2)" << "|\n"
			<< std::setw(13) << "_____________" << "|" << std::setw(10) << "__________" << "||" << std::setw(6) << "______" << "|" << std::setw(6) << "______" << "||" << std::setw(6) << "______" << "|" << std::setw(6) << "______" << "|\n"
			<< std::setw(13) << ""			    << "|" << std::setw(10) << ""			<< "||" << std::setw(6) << ""		<< "|" << std::setw(6) << ""	   << "||" << std::setw(6) << ""	   << "|" << std::setw(6) << ""		  << "|\n";
		auto start = std::chrono::high_resolution_clock::now();
		int kol = 1;
		std::cout << std::left <<"[" << std::setw(5) <<bottom_edge<<","<< std::setw(5)<<top_edge<<"]"<< "|" << std::setw(10) << interval << "||" << std::setw(6) << first_point.first << "|" << std::setw(6) << second_point.first << "||" << std::setw(6) << first_point.second << "|" << std::setw(6) << second_point.second << "|\n";
		///					Первый шаг
		if (first_point.second < second_point.second)
			{
				update_point1();
				update_point1();
			}
		else
			{
				update_point2();
				update_point2();
			}
		std::cout << std::left << "[" << std::setw(5) << bottom_edge << "," << std::setw(5) << top_edge << "]" << "|" << std::setw(10) << interval << "||" << std::setw(6) << first_point.first << "|" << std::setw(6) << second_point.first << "||" << std::setw(6) << first_point.second << "|" << std::setw(6) << second_point.second << "|\n";
		///					Второй шаг
		while (interval >= delta)
			{
				if (first_point.second < second_point.second)
					{
						update_point1();
						update_point1();

					}
				else
					{
						update_point2();
						update_point2();
					}
				if (second_point.first < first_point.first)
					{
						std::swap(second_point, first_point);
					}
				std::cout << std::left << "[" << std::setw(5) << bottom_edge << "," << std::setw(5) << top_edge << "]" << "|" << std::setw(10) << interval << "||" << std::setw(6) << first_point.first << "|" << std::setw(6) << second_point.first << "||" << std::setw(6) << first_point.second << "|" << std::setw(6) << second_point.second << "|\n";
				kol++;
			}
		auto end = std::chrono::high_resolution_clock::now();
		timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

		std::cout << "_______________________________________________________\n"
			<<"Результат: " << bottom_edge + (top_edge - bottom_edge) / 2 << "\n"
			<< "x* принадлежит [ " << bottom_edge << " , " << top_edge << " ] " << "\n"
			<< "--------------------------\n";;
		std::cout << "Время нахождения: " << timer.count() << " ns\n\n";
	}
