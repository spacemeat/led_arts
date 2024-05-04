#include "mistress.h"

Track::Track()
{
}

void Track::set_track_id(int track_id)
{
	_track_id = track_id;

	for (int r = 0; r < NumRocketsPerTrack; ++r)
	{
		_rockets[r]._track_id = track_id;
	}

	for (int s = 0; s < NumTracks * NumRocketsPerTrack; ++s)
	{
		_splashes[s]._track_id = track_id;
	}
}

void Track::set_splashes(Splash ** splashes)
{
	for (int r = 0; r < NumRocketsPerTrack; ++r)
	{
		_rockets[r].set_splashes(splashes + NumSplashesPerTrack / 2 * r);
	}
}

void Track::set()
{
#ifndef ARDUINO
	std::cout << "Track::set - " << _track_id << "; " << this << '\n';
#endif
	for (int r = 0; r < NumRocketsPerTrack; ++r)
	{
		_rockets[r].set();
	}
	for (int s = 0; s < NumSplashesPerTrack; ++s)
	{
		_splashes[s].set();
	}
}

void Track::reset()
{
	for (int r = 0; r < NumRocketsPerTrack; ++r)
	{
		_rockets[r].reset();
	}
	for (int s = 0; s < NumSplashesPerTrack; ++s)
	{
		_splashes[s].reset();
	}
}

void Track::animate(long ticks)
{
	for (int r = 0; r < NumRocketsPerTrack; ++r)
	{
		_rockets[r].animate(ticks);
	}
	for (int s = 0; s < NumSplashesPerTrack; ++s)
	{
		_splashes[s].animate(ticks);
	}
}

void Track::render()
{
	for (int r = 0; r < NumRocketsPerTrack; ++r)
	{
		_rockets[r].render();
	}
	for (int s = 0; s < NumSplashesPerTrack; ++s)
	{
		_splashes[s].render();
	}
}
