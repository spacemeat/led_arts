#ifdef ARDUINO
#include <FastLED.h>
#else

#include "system.h"
#include <chrono>


class MilliClock
{
public:
	long long millis()
	{
		auto now = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _start_time);
		return elapsed.count();
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> _start_time = std::chrono::steady_clock::now();
};


long millis()
{
    static MilliClock clock {};
	return static_cast<long>(clock.millis());
}

#endif

CHSV makeRandomColor()
{
    return CHSV(random(256), 128 + random(128), 128 + random(128));
}

CHSV makeRandomColor(CHSV inContrastTo)
{
    int offsetAbs = 256 / 6 + random(256/12);
    int posOrNeg = 1 - 2 * random(2);
    return CHSV(((256 + inContrastTo.h + posOrNeg * offsetAbs) % 256),
                128 + random(128),
                255 - inContrastTo.v);
}

