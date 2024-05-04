#include "mistress.h"

Splash::Splash()
{
}

void Splash::set()
{
#ifndef ARDUINO
	std::cout << "Splash::set - " << _track_id << "; " << this << '\n';
#endif
	reset();
}

void Splash::reset()
{
	_active = false;
	_prev_pos = _pos = 0;
	_vel = 0;
	_acc = 0;
}

void Splash::animate(long ticks)
{
	if (_active == false)
		{ return; }

	_vel += _acc * ticks;
	_prev_pos = _pos;
	_pos += _vel * ticks;

	if (_prev_pos < 0)
	{
		reset();
	}
}

void Splash::render()
{
	if (_active == false)
		{ return; }

	CRGB * buf = & frame_buffer[_track_id * NumLedsPerTrack];
	CRGB col = CRGB(_hsv);

	auto p = _pos / 1024 / 1024;
	if (p >= 0)
	{
		buf[p] = col;
	}

	// light up any skipped pixels for fast-movers
	auto pp = _prev_pos / 1024 / 1024;
	for (int pt = p; pt < pp; ++pt)
	{
		if (pt >= 0)
		{
			buf[pt] = col;
		}
	}
}
