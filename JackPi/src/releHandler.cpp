#include "../header/releHandler.h"

ReleHandler::ReleHandler(int _pin)
{
	pin = _pin;
	status = false;
}

bool ReleHandler::setOnRele(int level)
{
	if (level == 1 && status == false)
	{
		std::cout << "sono io" << std::endl;
		status = true;
		gpioWrite(pin, 0);
		std::thread delay(&ReleHandler::delayHandler, this);
		delay.detach();
	}
	return false;
}

void ReleHandler::delayHandler()
{
	gpioDelay(4000000);
	status = false;
	gpioWrite(pin, 1);
}