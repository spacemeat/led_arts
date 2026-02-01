#ifndef ARDUINO

#include "init_dot_d.h"
#include <iostream>

constexpr auto off = "\e[0m\e[48;2;0;0;0m";
constexpr auto clear_line = "\e[K";

int term_w = 80;
int term_h = 24;

int skipLines = NumPixelsPerBoardY + 2;

void report_effects()
{
    std::cout << off
		      << "\e[" << skipLines << "A";

	int w = term_w;
	int h = term_h;

	std::cout << off
			  << clear_line << "w: " << w << "; h: " << h << " t:" << animator.get_time() << '\n';
    //std::cout << clear_line << "c0: " << display.get_mandel_board().c0.real() << ", " << display.get_mandel_board().c0.imag() << "\n";
    //std::cout << clear_line << "c1: " << display.get_mandel_board().c1.real() << ", " << display.get_mandel_board().c1.imag() << "\n";
}

void show_leds()
{
    auto & pixel_board = display.get_pixel_board();
    for (int py = 0; py < NumPixelsPerBoardY; py += 2)
    {
        for (int px = 0; px < NumPixelsPerBoardX; ++px)
        {
            CRGB const & rgb0 = pixel_board.get_pixel(px, py);
            CRGB rgb1 = CRGB{0, 0, 0};
            if (py + 1 < NumPixelsPerBoardY) {
                rgb1 = pixel_board.get_pixel(px, py + 1);
            }
            std::cout << "\e[38;2;" << (int) rgb0.r << ";" << (int) rgb0.g << ";" << (int) rgb0.b << "m"
                      << "\e[48;2;" << (int) rgb1.r << ";" << (int) rgb1.g << ";" << (int) rgb1.b << "m▀";
        }
        std::cout <<"\n";
    }
}

void setup()
{
	std::cout << "Starting..." << '\n';
	display.reset();

    //display.get_board().report();

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
