#include "mistress.h"

Display::Display()
{
	for (int i = 0; i < NumTracks; ++i)
	{
		_tracks[i].set_track_id(i);
	}

	int s = 0;
	for (int t0 = 0; t0 < NumTracks; ++t0)
	{
		for (int r = 0; r < NumRocketsPerTrack; ++r)
		{
			for (int t1 = 0; t1 < NumTracks; ++t1)
			{
				_splashePtrs[s++] = & _tracks[t1]._splashes[NumRocketsPerTrack * t0 + r];
			}
		}
		_tracks[t0].set_splashes(_splashePtrs + NumRocketsPerTrack * NumTracks * t0);
	}
}

void Display::set()
{
	for (int i = 0; i < NumTracks; ++i)
	{
		_tracks[i].set();
	}
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
	for (int i = 0; i < NumTracks; ++i)
	{
		_tracks[i].animate(ticks);
	}
}

void Display::render()
{
	// fade previous frame
	for (unsigned int b = 0; b < sizeof(frame_buffer) / sizeof(frame_buffer[0]); ++b)
	{
		CRGB rgb = frame_buffer[b];
		frame_buffer[b] = CRGB((int) rgb.r * 7 / 8,
	                           (int) rgb.g * 7 / 8,
	                           (int) rgb.b * 7 / 8);
	}
	for (int i = 0; i < NumTracks; ++i)
	{
		_tracks[i].render();
	}
}

Display display;
