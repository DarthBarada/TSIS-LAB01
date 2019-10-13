#include "../include/OptimalPassiveSearch.h"

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
		std::multimap< long double, std::pair<long double, long double>> function_results; //Êîíòåéíåð óïîðÿäî÷åííûõ çíà÷åíèé äëÿ õðàíåíèÿ çíà÷åíèé ôóíêöèè

		setlocale(LC_ALL, "RU");
		std::cout << std::left << "Îïòèìàëüíûé ïàññèâíûé ïîèñê\n"
			<< "___________________________\n"
			<< "|" << std::setw(11) << "Êîëè÷åñòâî" << "|" << std::setw(11) << "Çíà÷åíèå x" << "|\n"
			<< "|" << std::setw(11) << "òî÷åê (N)" << "|" << std::setw(11) << "â ìèíèìóìå" << "|\n"
			<< "---------------------------\n";

		auto start = std::chrono::high_resolution_clock::now();

		for (int N = 1; length_of_undefined_segment(N) >= 2 * delta; N++)
			{
				function_results.clear();				// Ðàñïîëàãàòüñÿ äîëæíî çäåñü,÷òîáû ïðè ïîñëåäíåé èòåðàöèè íå ñòåðëî
				for (int k = 1; k <= N; k++)
					{
						dotx = bottom_edge + k * (top_edge - bottom_edge) / (N + 1.0);
						function_results.insert(std::make_pair(F(dotx), std::make_pair(dotx, length_of_undefined_segment(N) / 2)));
					}
				auto info = function_results.begin();
				std::cout << std::setprecision(4) << "|" << std::setw(11) << N << "|" << round(info->second.first * 1000) / 1000 << "±" << info->second.second << "\n";
			}
		std::cout << "--------------------------\n";
		auto end = std::chrono::high_resolution_clock::now();
		timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
		std::cout << "Âðåìÿ íàõîæäåíèÿ: " << timer.count() << " ns\n";
	}
