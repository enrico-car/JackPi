#pragma once

#include <iostream>
#include <pigpio.h>
#include <thread>

class ReleHandler {
	private:
	int pin;
	bool status;

	public:
	ReleHandler(int _pin);
	bool setOnRele(int level);
	void delayHandler();
};
