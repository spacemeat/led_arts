#ifndef __linux__
#error This code unit must be compiled for a linux environment.
#endif

#include "init_dot_d.h"
#include <iostream>

constexpr auto cursor_off = "\e[?25l";
constexpr auto off = "\e[0m\e[48;2;0;0;0m";
constexpr auto clear_line = "\e[K";

int term_w = 80;
int term_h = 24;
int skipLines = NumPixelsPerBoardY + 2;

static void clear()
{
    std::cout << off
		      << "\e[" << skipLines << "A";
}

static void report_debug_info()
{
	int w = term_w;
	int h = term_h;

	std::cout << off
			  << clear_line << "w: " << w << "; h: " << h << " t:" << animator.get_time() << '\n';
}

static void show_leds()
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

void setup_hardware()
{
	std::cout << cursor_off << "Starting..." << '\n';
	for (int i = 0; i < skipLines; ++i)
	{
        std::cout << '\n';
	}
}

void present()
{
    clear();
    report_debug_info();
	show_leds();
}


