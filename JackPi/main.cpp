#include <cstdio>
#include <pigpio.h>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <signal.h>
#include <map>
#include "header/BuzzerArchive.h"
#include "header/releHandler.h"
#include "header/buzzerHandler.h"

constexpr auto RELE_PIN = 14;
constexpr auto BUZZ_PIN = 15;
constexpr auto MIC_PIN = 4;

void SignalHandler(int);
void OnPinHigh(int, int, uint32_t);
int lastLevel = 0;
ReleHandler rele(RELE_PIN);
BuzzerHandler buzzer(BUZZ_PIN);

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
	}

	return EXIT_SUCCESS;
}

void SignalHandler(int)
{
	//gpioWrite(BUZZ_PIN, PI_LOW);
	rele.setOnKill();
	buzzer.setOnKill();
	gpioTerminate();
	exit(EXIT_SUCCESS);
}

void OnPinHigh(int pin, int level, uint32_t tick)
{
	rele.setOnRele(10);
	buzzer.setOnBuzzer(megalovania_melody, megalovania_tempo, 140);
}