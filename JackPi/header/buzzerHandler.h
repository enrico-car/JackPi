#pragma once

#include <iostream>
#include <pigpio.h>
#include <thread>
#include <vector>

class BuzzerHandler {
	private:
	int pin;
	bool onFlag;

	void playSong(const std::vector<int>& melody, const std::vector<int>& tempo, int bpm);
	void buzz(long frequency, long length, int bpm);

	public:
	BuzzerHandler(int _pin);
	void setOnBuzzer(const std::vector<int>& melody, const std::vector<int>& tempo, int bpm);
	void setOnKill();
};