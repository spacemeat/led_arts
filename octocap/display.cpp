#include "octocap.h"

Display::Display()
: _octopus{}
{
}

void Display::set()
{
    _octopus.set();
	for (unsigned int b = 0; b < sizeof(frame_buffer) / sizeof(frame_buffer[0]); ++b)
	{
		frame_buffer[b] = CRGB(0, 0, 0);
	}
}

void Display::reset()
{
	set();
}

void Display::animate(long ticks)
{
    _octopus.animate(ticks);
}

void Display::render()
{
    _octopus.render();
}

Display display;

