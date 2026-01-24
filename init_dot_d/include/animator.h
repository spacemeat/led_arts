#pragma once

#include "system.h"


class Animator
{
public:
    Animator();
    long get_time();
    void wait_for_frame();
    void tick();

private:
    long _prev_time;
    long _time;
};

