#include "octocap.h"

Tentacle::Tentacle()
{
}

void Tentacle::set()
{
#ifndef ARDUINO
	std::cout << "Tentacle::set - " << _tentacle_id << "; " << this << '\n';
#endif
}

void Tentacle::reset()
{
}

void Tentacle::animate(long ticks)
{
}

void Tentacle::render()
{
}

