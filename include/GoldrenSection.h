#pragma once
#include <iostream>
#include <map>
#include <chrono>

#include "MyFunction.h"

class GoldrenSection: public MyFunction
	{
		long double top_edge;					 // ������� ������� �������
		long double bottom_edge;				 // ������ ������� �������
		long double delta;						 // ��������
		std::chrono::nanoseconds timer;	     // ����� ���������� ������������ ���������

		long double interval;					// ����� ���������

		std::pair<long double, long double> first_point;	// ����� 1 / �������� 1
		std::pair<long double, long double> second_point;	// ����� 2 / �������� 2

		const long double t = (1.0 + sqrt(5)) / 2.0;
	public:

		GoldrenSection();

		// ������� �����������
		GoldrenSection(long double bottom, long double top, long double e = 0.1);

		~GoldrenSection()
			{}

		void update_interval();

		/*������� ���������� ������ �����
		   ���� ��� ������, �� ��������� ��, ���� ���,
		   �� ������ ����� �������� 1 � 2 ����� �������*/
		void update_point1();
		/*������� ���������� ������ �����
		   ���� ��� ������, �� ��������� ��, ���� ���,
		   �� ������ ����� �������� 2 � 1 ����� �������*/
		void update_point2();

		// ������ ���������� 1 ���� ����� 1 ���2  - ������ ���������
		bool point1_empty()
			{
				return (first_point.first == 0.0) && (first_point.second == 0.0);
			}
		bool point2_empty()
			{
				return (second_point.first == 0.0) && (second_point.second == 0.0);
			}

		// ������� �������� ��� ����������� ����������
		void pass();
	};
