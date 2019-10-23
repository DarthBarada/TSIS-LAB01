#include "GoldrenSection.h"
#include <iomanip>

GoldrenSection::GoldrenSection(long double bottom, long double top, long double accuracy)
	{
		top_edge = top; bottom_edge = bottom; delta = accuracy;
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
		unsigned int iteration=0;
		std::cout <<std::left<<"\nGolden-section search\n"
			<< " _______________________________________________________________________________________\n"
			<<"|"<<std::setw(11)<<""         <<"|"<<  std::setw(21) << "" 							       << "|" << std::setw(11) << "  Length" 	 << "||" << std::setw(9) << 	 " "	    << "|" << std::setw(9) << 		" "	    << "||" << std::setw(9) << 		" "		   << "|" << std::setw(9) << 	" "		    << "|\n"
			<<"|"<<std::setw(11)<<" Iteration"<<"|"<<  std::setw(21) <<"       Interval"       << "|" << std::setw(11) << "of interval"  << "||" << std::setw(9) << "   X1"    << "|" << std::setw(9) << "   X2"    << "||" << std::setw(9) << "  F(X1)"  << "|" << std::setw(9) << "  F(X2)"   << "|\n"
			<<"|"<<std::setw(11)<<"___________"<<"|"<<  std::setw(21) << "_____________________"<< "|" << std::setw(11) << "___________"  << "||" << std::setw(9) << "_________" << "|" << std::setw(9) << "_________" << "||" << std::setw(9) << "_________" << "|" << std::setw(9) << "_________"<< "|\n"
			<<"|"<<std::setw(11)<<""         <<"|"<<  std::setw(21) << ""			    		       << "|" << std::setw(11) << ""						 << "||" << std::setw(9) << ""			    << "|" << std::setw(9) << ""          << "||" << std::setw(9) << ""          << "|" << std::setw(9) << ""		      << "|\n";
		auto start = std::chrono::high_resolution_clock::now();
		std::cout <<std::showpos<<std::fixed<<std::setprecision(6)<<"|"<<std::setw(11)<<iteration<<"|"<<  std::left <<"[" << std::setw(9) <<bottom_edge<<","<< std::setw(9)<<top_edge<<"]"<< "| " << std::setw(10) << interval << "||" << std::setw(9) << first_point.first << "|" << std::setw(9) << second_point.first << "||" << std::setw(9) << first_point.second << "|" << std::setw(9) << second_point.second << "|\n";
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
		++iteration;
		std::cout <<std::showpos<<std::fixed<<std::setprecision(6)<<"|"<<std::setw(11)<<iteration<<"|"<<  std::left << "[" << std::setw(9) << bottom_edge << "," << std::setw(9) << top_edge << "]" << "| " << std::setw(10) << interval << "||" << std::setw(9) << first_point.first << "|" << std::setw(9) << second_point.first << "||" << std::setw(9) << first_point.second << "|" << std::setw(9) << second_point.second << "|\n";
		///					Второй шаг
		while (interval >= 2 * delta)
			{
				++iteration;
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
				std::cout <<std::showpos<<std::fixed<<std::setprecision(6)<<"|"<<std::setw(11)<<iteration<<"|"<<  std::left << "[" << std::setw(9) << bottom_edge << "," << std::setw(9) << top_edge << "]" << "| " << std::setw(10) << interval << "||" << std::setw(9) << first_point.first << "|" << std::setw(9) << second_point.first << "||" << std::setw(9) << first_point.second << "|" << std::setw(9) << second_point.second << "|\n";

			}
		auto end = std::chrono::high_resolution_clock::now();
		timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

		std::cout<<std::noshowpos<<std::fixed<<std::setprecision(6)<<"|"<<std::setw(11)<<"___________"<<"|"<< std::setw(21) << "_____________________"<< "|" << std::setw(11) << "___________"  << "||" << std::setw(9) << "_________" << "|" << std::setw(9) << "_________" << "||" << std::setw(9) << "_________" << "|" << std::setw(9) << "_________"<< "|\n"
			<<"\nResult: " << F(bottom_edge + (top_edge - bottom_edge) / 2.0) << "\n"
			<< "x* belongs [ " << bottom_edge << " , " << top_edge << " ] " << "\n"
			<<"x* = "<<bottom_edge + (top_edge-bottom_edge)/2.0<<"\n"
			<< "-----------------------------------------\n";
		//std::cout << "Working time: " << timer.count() << " ns\n\n";
	}
