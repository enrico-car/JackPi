#include "../header/micHandler.h"

void onPinHigh(MicHandler& mic)
{
	//gpioSetAlertFunc(mic.getPin(), );
}

MicHandler::MicHandler(int _pin)
{
	pin = _pin;
	gpioSetMode(pin, PI_INPUT);
}

int MicHandler::getPin()
{
	return pin;
}