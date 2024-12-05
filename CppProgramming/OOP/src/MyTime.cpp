/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#include "MyTime.h"

namespace OOP {
	MyTime::MyTime() {
		setTime(std::time(0));
	}

	MyTime::MyTime(long long elapseTime) {
		setTime(elapseTime);
	}

	MyTime::MyTime(int hour, int minute, int second) {
		this->hour = hour;
		this->minute = minute;
		this->second = second;
	}

	int MyTime::getHour() {
		return hour;
	}

	int MyTime::getMinute() {
		return minute;
	}

	int MyTime::getSecond() {
		return second;
	}

	void MyTime::setTime(long long elapseTime) {
		elapseTime--;
		this->hour = elapseTime / 3600 % 24;
		this->minute = elapseTime / 60 % 60;
		this->second = elapseTime % 60;
	}
}
