#include "mistress.h"

Rocket::Rocket()
{
}

void Rocket::set_splashes(Splash ** splash_ptrs)
{
	_splash_ptrs = splash_ptrs;
}


void Rocket::set()
{
#ifndef ARDUINO
	std::cout << "Rocket::set - " << _track_id << "; " << this << '\n';
	for (int i = 0; i < NumTracks; ++i)
	{
		std::cout << " - Splash: " << _splash_ptrs[i] << '\n';
	}
#endif
	reset();
}

void Rocket::reset()
{
	_time_to_start = random(4000, 20000);
	_prev_pos = _pos = random(NumLedsPerTrack * 3 / 4 * 1000000, NumLedsPerTrack * 1000000);
	_vel = - random(10000);
	_acc = -50;
	_max_hsv = CHSV(random(256), 128 + random(128), random(max_power * 3 / 4, max_power));
	_current_hsv = CHSV(_max_hsv.h, 0, _max_hsv.v / 4); 
	_init_hsv = _current_hsv;
}

void Rocket::animate(long ticks)
{
	_time_to_start -= ticks;

	if (_time_to_start > 0)
		{ return; }

	_prev_pos = _pos;
	_vel += _acc * ticks;
	_pos += _vel * ticks;

	auto iv = NumLedsPerTrack * 1024 / 2;
	auto pf = max(0, _pos / 1024 - iv);
	auto df = iv - pf;
	_current_hsv.s = (long) (_init_hsv.s * pf) / iv + (long) (_max_hsv.s * df) / iv;
	_current_hsv.v = (long) (_init_hsv.v * pf) / iv + (long) (_max_hsv.v * df) / iv;

	if (_pos < 0)
	{
		for (int s = 0; s < NumTracks; ++s)
		{
			int dist = (abs(s - _track_id) + NumTracks) % NumTracks;
			dist *= dist;
			_splash_ptrs[s]->_active = true;
			_splash_ptrs[s]->_pos = 0;
			_splash_ptrs[s]->_vel = - _vel / 6 - _vel * (NumTracks - dist) / NumTracks / 6;
			_splash_ptrs[s]->_acc = _acc;
			_splash_ptrs[s]->_hsv = _current_hsv;
		}
	}

	if (_prev_pos < 0)
	{
		reset();
	}
}

void Rocket::render()
{
	if (_time_to_start > 0)
		{ return; }

	CRGB * buf = & frame_buffer[_track_id * NumLedsPerTrack];
	CRGB col = CRGB(_current_hsv);

	// always light up at least one
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

#ifndef ARDUINO
std::ostream & operator << (std::ostream & os, Rocket const & rhs)
{
	os << "pos: " << std::setw(9) << rhs._pos
	   << "; prev_pos: " << std::setw(9) << rhs._prev_pos
	   << "; tts: " << std::setw(5) << rhs._time_to_start
	   << "; vel: " << std::setw(7) << rhs._vel
	   << "; cur: " << std::setw(3) << (int) rhs._current_hsv.h
	   << ", "  << std::setw(3) << (int) rhs._current_hsv.s
	   << ", "  << std::setw(3) << (int) rhs._current_hsv.v
	   << '\n';

	return os;
}
#endif
