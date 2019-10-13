#pragma once
#include <iostream>
#include <map>
#include <chrono>

#include "MyFunction.h"

class OptimalPassiveSearch: public MyFunction
	{
		long double top_edge;					     // ������� ������� �������
		long double bottom_edge;					 // ������ ������� �������
		long double delta;						     // ��������
		std::pair<long double, long double> point;
		std::chrono::nanoseconds timer;	         // ����� ���������� ������������ ���������
		public:


			// ������� �����������
			OptimalPassiveSearch(long double bottom, long double top, long double e = 0.1);

			~OptimalPassiveSearch()
			{}

			// ������� ��������� �����������
			double length_of_undefined_segment(int N);

			// ������� �������� ��� ����������� ����������
			void pass();
	};
