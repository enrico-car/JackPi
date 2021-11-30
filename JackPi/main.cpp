#include <cstdio>
#include <pigpio.h>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <signal.h>
#include <map>
#include "header/BuzzerArchive.h"
#include "header/releHandler.h"

constexpr auto RELE_PIN = 14;
constexpr auto BUZZ_PIN = 15;
constexpr auto MIC_PIN = 4;

void SignalHandler(int);
void OnPinHigh(int, int, uint32_t);
int lastLevel = 0;
ReleHandler rele(RELE_PIN);

int main(int argc, char* argv[])
{
	if (gpioInitialise() < 0)
	{
		std::cerr << "Error initialising GPIO PigPio" << std::endl;
		exit(0);
	}

	gpioSetSignalFunc(SIGINT, SignalHandler);
	gpioSetSignalFunc(SIGKILL, SignalHandler);
	gpioSetSignalFunc(SIGTERM, SignalHandler);

	gpioSetMode(MIC_PIN, PI_INPUT);
	gpioSetAlertFunc(MIC_PIN, OnPinHigh);
	while (true)
	{
		//for (int i = 0; i < sizeof(santa_melody) / sizeof(int); i++)
		//{
		//	// to calculate the note duration, take one second
		//	// divided by the note type.
		//	//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
		//	int noteDuration = santa_tempo[i];

		//	buzz(BUZZ_PIN, santa_melody[i], noteDuration);

		//	// to distinguish the notes, set a minimum time between them.
		//	// the note's duration + 30% seems to work well:
		//	int pauseBetweenNotes = (int)(noteDuration * 1.30);
		//	gpioDelay(pauseBetweenNotes);
		//}
	}

	return EXIT_SUCCESS;
}

void SignalHandler(int)
{
	gpioWrite(RELE_PIN, PI_HIGH);
	gpioWrite(BUZZ_PIN, PI_LOW);
	gpioTerminate();
	exit(EXIT_SUCCESS);
}

void OnPinHigh(int pin, int level, uint32_t tick)
{
	rele.setOnRele(level);
}