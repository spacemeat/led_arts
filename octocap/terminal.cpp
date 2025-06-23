#ifndef ARDUINO

#include "octocap.h"
#include <iostream>

constexpr auto off = "\e[0m\e[48;2;0;0;0m";
constexpr auto clear_line = "\e[K";

int term_w = 80;
int term_h = 24;

void show_leds()
{
	int p = 0;
	int w = term_w;
	int h = term_h;

	std::cout << off
		      << "\e[" << h - NumTentacles * 3 - 2 << ";"<< 0 << "H"
			  << clear_line << "w: " << w << "; h: " << h << " t:" << animator.get_time() << '\n';
	for (int t = 0; t < NumTentacles; ++t)
	{
		for (int l = 0; l < NumLedsPerTentacle; ++l)
		{
			CRGB const & rgb = frame_buffer[p++];
		    std::cout << "\e[38;2;" << (int) rgb.r << ";" << (int) rgb.g << ";" << (int) rgb.b << "m*";
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

void setup()
{
	std::cout << "Starting..." << '\n';
	display.set();

	for (int i = 0; i < NumTentacles * 3 + 2; ++i)
	{
		std::cout << '\n';
	}
}

void loop()
{
	animator.wait_for_frame();
	animator.tick();
	display.render();
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
