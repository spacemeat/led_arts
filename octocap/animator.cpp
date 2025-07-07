#include "octocap.h"


CRGB frame_buffer[NumLedsInMantle + NumLedsInTentacles];

Animator::Animator()
{
}

void Animator::wait_for_frame()
{
	auto time = _time;
	while (time - _prev_time < FramePeriodInMs)
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
