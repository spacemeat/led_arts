#include "octocap.h"


Octopus::Octopus()
{
	for (int i = 0; i < NumBands; ++i)
	{
		_mantleBands[i].set_band_id(i);
	}
	for (int i = 0; i < NumTentacles; ++i)
	{
		_tentacles[i].set_tentacle_id(i);
	}
}

void Octopus::set()
{
	for (int i = 0; i < NumBands; ++i)
	{
		_mantleBands[i].set();
	}
	for (int i = 0; i < NumTentacles; ++i)
	{
		_tentacles[i].set();
	}
	for (unsigned int b = 0; b < sizeof(frame_buffer) / sizeof(frame_buffer[0]); ++b)
	{
		frame_buffer[b] = CRGB(0, 0, 0);
	}
}

void Octopus::reset()
{
	set();
}

void Octopus::animate(long ticks)
{
	for (int i = 0; i < NumBands; ++i)
	{
		_mantleBands[i].animate(ticks);
	}
	for (int i = 0; i < NumTentacles; ++i)
	{
		_tentacles[i].animate(ticks);
	}
}

void Octopus::render()
{
	// fade previous frame
	for (int i = 0; i < NumBands; ++i)
	{
		_mantleBands[i].render();
	}
	for (int i = 0; i < NumTentacles; ++i)
	{
		_tentacles[i].render();
	}
}


