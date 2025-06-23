#ifndef ARDUINO

#include "system.h"
#include <chrono>

int abs(int v)
{
	return v < 0 ? -v : v;
}

int min(int a, int b)
{
	return a < b ? a : b;
}

int max(int a, int b)
{
	return a >= b ? a : b;
}

int random(int n)
{
	return rand() % n;
}

int random(int n, int x)
{
	return (rand() % (x - n)) + n;
}

class MilliClock
{
public:
	MilliClock()
	: _start_time(std::chrono::steady_clock::now())
	{
	}
	
	long long millis() const
	{
		auto now = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _start_time);
		return elapsed.count();
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> _start_time;
};

MilliClock millis_clock;

long millis()
{
	return (long) millis_clock.millis();
}

#endif

