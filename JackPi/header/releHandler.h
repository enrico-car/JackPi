#pragma once

#include <iostream>
#include <pigpio.h>
#include <thread>

class ReleHandler {
	private:
	int pin;
	bool status;

	void delayHandler(int time);

	public:
	ReleHandler(int _pin);
	void setOnRele(int timeSec);
	void setOnKill();
};
