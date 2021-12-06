#include "../header/buzzerHandler.h"

BuzzerHandler::BuzzerHandler(int _pin)
{
	pin = _pin;
	onFlag = false;
}

void BuzzerHandler::setOnBuzzer(const std::vector<int>& melody, const std::vector<int>& tempo, int bpm)
{
	if (!onFlag)
	{
		onFlag = true;
		std::thread song(&BuzzerHandler::playSong, this, melody, tempo, bpm);
		song.detach();
	}
}

void BuzzerHandler::setOnKill()
{
	onFlag = false;
	gpioWrite(pin, PI_LOW);
}

void BuzzerHandler::playSong(const std::vector<int>& melody, const std::vector<int>& tempo, int bpm)
{
	for (int i = 0; i < melody.size(); i++)
	{
		if (onFlag)
		{
			int noteDuration = tempo[i];

			buzz(melody[i] / 2, noteDuration, bpm);

			long sixTeenthDelay = (60 * 1000000 / bpm) / 4;
			int pauseBetweenNotes = (int)(noteDuration * sixTeenthDelay * 0.2);
			gpioDelay(pauseBetweenNotes);
		}
	}
	onFlag = false;
}

void BuzzerHandler::buzz(long frequency, long length, int bpm)
{
	long sixTeenthDelay = (60 * 1000000 / bpm) / 4;

	if (frequency <= 0)
	{
		gpioDelay(sixTeenthDelay * length);
		return;
	}

	long delay = 1000000 / frequency;
	long hDelay = delay / 2;
	long numCycles = sixTeenthDelay * length / delay;

	for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
		gpioWrite(pin, PI_HIGH); // write the buzzer pin high to push out the diaphram
		gpioDelay(hDelay); // wait for the calculated delay value
		gpioWrite(pin, PI_LOW); // write the buzzer pin low to pull back the diaphram
		gpioDelay(hDelay); // wait again or the calculated delay value
	}
}