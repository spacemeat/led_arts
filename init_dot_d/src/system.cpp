#include "init_dot_d.h"

#ifndef ARDUINO

#include <chrono>
#include <signal.h>

void setup();
void loop();

class MilliClock
{
public:
	long long millis()
	{
		auto now = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _start_time);
		return elapsed.count();
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> _start_time = std::chrono::steady_clock::now();
};


long millis()
{
    static MilliClock clock {};
	return static_cast<long>(clock.millis());
}

#endif

CHSV makeRandomColor()
{
    return CHSV(random(256), 128 + random(128), 128 + random(128));
}

CHSV makeRandomColor(CHSV inContrastTo)
{
    int offsetAbs = 256 / 6 + random(256/12);
    int posOrNeg = 1 - 2 * random(2);
    return CHSV(((256 + inContrastTo.h + posOrNeg * offsetAbs) % 256),
                128 + random(128),
                255 - inContrastTo.v);
}

void setup()
{
    setup_hardware();
	display.reset();
}

void loop()
{
	animator.wait_for_frame();
	animator.tick();
	display.render();
    present();
}


#ifndef ARDUINO

void sigint_handler([[maybe_unused]] int sig)
{
    // cursor on, remove color formatting
    std::cout << "\e[?25h\e[0m\e[48;2;0;0;0m" << std::endl;

    signal(SIGINT, SIG_DFL);
    raise(SIGINT);
}

int main(int argc, char* argv[])
{
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
    {
        perror("signal");
        return 1;
    }

	if (argc > 1)
		{ term_w = atoi(argv[1]); }
	if (argc > 2)
		{ term_h = atoi(argv[2]); }

	setup();

	for(;;)
	{
        loop();
	}

	return 0;
}

#endif

