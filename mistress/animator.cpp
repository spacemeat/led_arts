#include "mistress.h"


CRGB frame_buffer[NumTracks * NumLedsPerTrack];

Animator::Animator()
{
}

void Animator::wait_for_frame()
{
	auto time = _time;
	while (time - _prev_time < FramePeriod)
	{
		time = millis();
	}
}

void Animator::tick()
{
	_prev_time = _time;
	_time = millis();

	display.animate(_time - _prev_time);
}

Animator animator;
