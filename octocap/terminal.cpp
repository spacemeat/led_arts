#ifndef ARDUINO

#include "octocap.h"
#include "effects/effect.h"
#include <iostream>

constexpr auto off = "\e[0m\e[48;2;0;0;0m";
constexpr auto clear_line = "\e[K";

int term_w = 80;
int term_h = 24;

int skipLines = NumTentacles * 3 + 12;
void report_effects()
{
    std::cout << off
		      << "\e[" << term_h - skipLines << ";"<< 0 << "H";

    auto controller = display._octopus.get_controller();

    auto effect = controller->get_effect_A();
    effect->report();

    effect = controller->get_effect_B();
    effect->report();

    controller->report();
}

void show_leds()
{
	int w = term_w;
	int h = term_h;

	std::cout << off
			  << clear_line << "w: " << w << "; h: " << h << " t:" << animator.get_time() << '\n';
	for (int t = 0; t < NumTentacles; ++t)
	{
        int fbs = display._octopus._tentacles[t]._frame_buffer_start;
		for (int l = 0; l < NumLedsPerTentacle; ++l)
		{
			CRGB const & rgb = frame_buffer[fbs + l];
            std::cout << "\e[38;2;" << (int) rgb.r << ";" << (int) rgb.g << ";" << (int) rgb.b << "m*";
            //if (l < 8) { std::cout << (int) rgb.r << "; " <<(int)  rgb.g << "; " <<(int)  rgb.b << "      "; }
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

void setup()
{
	std::cout << "Starting..." << '\n';
	display.reset();

	for (int i = 0; i < skipLines; ++i)
	{
		std::cout << '\n';
	}
}

void loop()
{
	animator.wait_for_frame();
	animator.tick();
	display.render();
    report_effects();
	show_leds();
}

int main(int argc, char* argv[])
{
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
