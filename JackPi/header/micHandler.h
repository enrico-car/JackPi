#pragma once

#include <iostream>
#include <pigpio.h>
#include <functional>
#include <vector>

class MicHandler {
	private:
	int pin;
	std::vector<std::function<void()>> callOnHigh;

	public:
	MicHandler(int _pin);
	int getPin();
};
