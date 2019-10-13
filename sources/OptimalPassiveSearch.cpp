#include "OptimalPassiveSearch.h"
#include <iomanip>

OptimalPassiveSearch::OptimalPassiveSearch(long double bottom, long double top, long double e)
	{
		top_edge = top; bottom_edge = bottom; delta = e;
	}

double OptimalPassiveSearch::length_of_undefined_segment(int N)
	{
		return 2.0*(top_edge - bottom_edge) / (N + 1.0);
	}

void OptimalPassiveSearch::pass()
	{
		double dotx = 0;
		std::multimap< long double, std::pair<long double, long double>> function_results; //Контейнер упорядоченных значений для хранения значений функции

	 /*std::cout << std::left << "Оптимальный пассивный поиск\n"
			<< "___________________________\n"
			<< "|" << std::setw(12) << "Количество" << "|" << std::setw(12) << "Значение x" << "|\n"
			<< "|" << std::setw(12) << "точек (N)" << "|" << std::setw(12) << "в минимуме" << "|\n"
			<< "---------------------------\n";*/
		std::cout << std::left << "Optimal passive search\n"
				<< "_____________________________\n"
				<< "|" << std::setw(13) << "Count" << "|" << std::setw(13) << "Value x" << "|\n"
				<< "|" << std::setw(13) << "of points (N)" << "|" << std::setw(13) << "in minimum" << "|\n"
				<< "|" << std::setw(13) << "_____________" << "|" << std::setw(13) << "_____________" << "|\n";

		auto start = std::chrono::high_resolution_clock::now();

		for (int N = 1; length_of_undefined_segment(N) >= 2 * delta; N++)
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
		std::cout << "|" << std::setw(13) << "_____________" << "|" << "_____________|" <<"\n";
		std::cout <<"Result: "<< round(point.first * 1000) / 1000 << "±" << point.second <<"\n"<< "----------------------------\n";
		auto end = std::chrono::high_resolution_clock::now();
		timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
		std::cout << "Working time: " << timer.count() << " ns\n";
	}
