#include "../header/releHandler.h"

ReleHandler::ReleHandler(int _pin)
{
	pin = _pin;
	status = false;
}

void ReleHandler::setOnRele(int timeSec)
{
	if (!status)
	{
		status = true;
		gpioWrite(pin, 0);
		std::thread delay(&ReleHandler::delayHandler, this, timeSec * 1000000);
		delay.detach();
	}
}

void ReleHandler::setOnKill() {
	gpioWrite(pin, PI_HIGH);
}

void ReleHandler::delayHandler(int time)
{
	gpioDelay(time);

	status = false;
	gpioWrite(pin, 1);
}