/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#pragma once
#include <ctime>

namespace OOP {
	class MyTime {
	public:
		MyTime();
		MyTime(long long);
		MyTime(int, int, int);
		int getHour();
		int getMinute();
		int getSecond();
		void setTime(long long);
	private:
		int hour;
		int minute;
		int second;
	};
}
