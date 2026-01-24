#include "init_dot_d.h"
#include "animator.h"

Animator::Animator()
{
    _time = _prev_time = millis();
}

long Animator::get_time()
{
    return _time;
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
