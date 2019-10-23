#include "OptimalPassiveSearch.h"
#include <iostream>
#include <iomanip>

OptimalPassiveSearch::OptimalPassiveSearch(double bottom,double top,double accuracy)
	{
		top_edge = top; bottom_edge = bottom; delta = accuracy;

		Value_N=double(((top_edge-bottom_edge)/delta)-1.0);
	}

double OptimalPassiveSearch::length_of_undefined_segment(int N)
	{
		return 2.0*(top_edge - bottom_edge) / (N + 1.0);
	}

void OptimalPassiveSearch::test_pass()
	{
		double dotx = 0;
		std::multimap<double, std::pair<double,double>> function_results; //Контейнер упорядоченных значений для хранения значений функции

		std::cout << std::left << "Optimal passive search\n"
				<< "_____________________________\n\n"
				<< "Prospective count of N: "<<Value_N<<"\n"
				<<"_____________________________\n"
				<< "|" << std::setw(13) << "    Count" << "|" << std::setw(13) << "    Value x" << "|\n"
				<< "|" << std::setw(13) << "of points (N)" << "|" << std::setw(13) << "  in minimum" << "|\n"
				<< "|" << std::setw(13) << "_____________" << "|" << std::setw(13) << "_____________" << "|\n";

		auto start = std::chrono::high_resolution_clock::now();

		for (int N = 1; length_of_undefined_segment(N) >= 2*delta; N++)
			{
				function_results.clear();				// Располагаться должно здесь,чтобы при последней итерации не стерло
				for (int k = 1; k <= N; k++)
					{
						dotx = bottom_edge + k * (top_edge - bottom_edge) / (N + 1.0);
						function_results.insert(std::make_pair(F(dotx), std::make_pair(dotx, length_of_undefined_segment(N) / 2)));
					}
				auto info = function_results.begin();
				point = info->second;
				std::cout << std::setprecision(4) << "|" << std::setw(13) << N << "|" << round(info->second.first * 1000) / 1000 << "±" << info->second.second <<"\n";
			}

		auto end = std::chrono::high_resolution_clock::now();

		std::cout << "|" << std::setw(13) << "_____________" << "|" << "_____________|" <<"\n";
		std::cout <<"\nResult: "<< round(point.first * 1000) / 1000 << "±" << point.second <<"\n"<< "----------------------------\n";

		timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
		std::cout << "Working time: " << timer.count() << " ns\n";
	}

	void OptimalPassiveSearch::pass()
		{
			std::pair <double,double> dot;

			std::multimap<double,double> function_results; //Контейнер упорядоченных значений для хранения значений функции

			std::cout << std::left << "Optimal passive search\n"
					<<" __________________________________\n"
					<< "|" << std::setw(14) << ""               << "|" << std::setw(9) << ""          << "|" <<std::setw(9)<<""        << "|\n"
					<< "|" << std::setw(14) << "   Number"      << "|" << std::setw(9) << "    x"     << "|" <<std::setw(9)<<"   F(x)"<< "|\n"
					<< "|" << std::setw(14) << " of point (k)"  << "|" << std::setw(9) << ""          << "|" <<std::setw(9)<<""<< "|\n"
					<< "|" << std::setw(14) << "______________" << "|" << std::setw(9) << "_________" << "|" <<std::setw(9)<<"_________"<< "|\n";

			auto start = std::chrono::high_resolution_clock::now();

			for (int k = 1; k <= Value_N; k++)
				{
					dot.first = bottom_edge + k * (top_edge - bottom_edge) / (Value_N + 1.0);
					dot.second = F(dot.first);
					std::cout<<std::noshowpos<<std::fixed<<std::setprecision(6)<< "|" << std::setw(14) << k << "|" <<std::showpos<< std::setw(9) << dot.first << "|" <<std::setw(9)<<dot.second<< "|\n";
					function_results.insert(std::make_pair(dot.second, dot.first));
				}

			auto end = std::chrono::high_resolution_clock::now();
			std::cout<< "|" << std::setw(14) << "______________" << "|" << std::setw(9) << "_________" << "|" <<std::setw(9)<<"_________"<< "|\n";

			auto info = function_results.begin();
			point = std::make_pair(info->second,info->first);

			std::cout<<std::setprecision(6)<<"\nBest result\n"
			<<" ____________________\n"
			<< "|" << std::setw(9) << ""          << "|" <<std::setw(9)<<""            << "|\n"
			<< "|" << std::setw(9) << "    x"     << "|" <<std::setw(9)<<"   F(x)"     << "|\n"
			<< "|" << std::setw(9) << "_________" << "|" <<std::setw(9)<<"_________"  << "|\n"
			<< "|" << std::setw(9) << point.first << "|" <<std::setw(9)<< point.second << "|\n"
			<< "|" << std::setw(9) << "_________" << "|" <<std::setw(9)<<"_________"  << "|\n";

			std::cout <<std::noshowpos<<std::fixed<<std::setprecision(6)<<"\nResult: "<<point.second<<"\n"
			<<"x* belongs "<< point.first << " ± " << length_of_undefined_segment(Value_N)/2 <<"\n"
			<< "-----------------------------------------\n";

			timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			//std::cout << "Working time: " << timer.count() << " ns\n";
		}
