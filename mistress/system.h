#ifndef MISTRESS_SYSTEM_H
#define MISTRESS_SYSTEM_H

#ifndef ARDUINO

#include <cstdint>
#include <cstdlib>
#include <time.h>

extern timespec boot_ts;

using u8 = std::uint8_t;

auto abs(auto v)
{
	return v < 0 ? -v : v;
}

auto min(auto a, auto b)
{
	return a < b ? a : b;
}

auto max(auto a, auto b)
{
	return a >= b ? a : b;
}

auto random(auto n)
{
	return rand() % n;
}

auto random(auto n, auto x)
{
	return (rand() % (x - n)) + n;
}

long millis();

struct CHSV
{
	CHSV()
	: h(0), s(0), v(0)
	{
	}

	CHSV(u8 h, u8 s, u8 v)
	: h(h), s(s), v(v)
	{
	}

	u8 h = 0;
	u8 s = 0;
	u8 v = 0;
};

struct CRGB
{
	CRGB()
	: r(0), g(0), b(0)
	{
	}

	CRGB(u8 r, u8 g, u8 b)
	: r(r), g(g), b(b)
	{
	}
	
	CRGB(CHSV hsv)
	{
		float s = hsv.s / 255.0f;
		float v = hsv.v / 255.0f;

		float c = v * s;
		float x = c * int(1 - abs((hsv.h / 6) % 2 - 1));
		float m = v - c;

		float fr = 0, fg = 0, fb = 0;
		if (hsv.h < 256 / 6)
			{ fr = c; fg = x; fb = 0; }
		if (hsv.h >= 256 / 6 * 1 && hsv.h < 256 / 6 * 2)
			{ fr = x; fg = c; fb = 0; }
		if (hsv.h >= 256 / 6 * 2 && hsv.h < 256 / 6 * 3)
			{ fr = 0; fg = c; fb = x; }
		if (hsv.h >= 256 / 6 * 3 && hsv.h < 256 / 6 * 4)
			{ fr = 0; fg = x; fb = c; }
		if (hsv.h >= 256 / 6 * 4 && hsv.h < 256 / 6 * 5)
			{ fr = x; fg = 0; fb = c; }
		if (hsv.h >= 256 / 6 * 5)
			{ fr = c; fg = 0; fb = x; }

		r = (fr + m) * 255;
		g = (fg + m) * 255;
		b = (fb + m) * 255;
	}

	CRGB& operator +=(CRGB rhs)
	{
		r = min(255, (int) r + (int) rhs.r);
		g = min(255, (int) g + (int) rhs.g);
		b = min(255, (int) b + (int) rhs.b);
		return *this;
	}

	CRGB operator +(CRGB rhs)
	{
		return CRGB(min(255, (int) r + (int) rhs.r),
		  		    min(255, (int) g + (int) rhs.g),
				    min(255, (int) b + (int) rhs.b));
	}

	u8 r = 0;
	u8 g = 0;
	u8 b = 0;
};

#endif // #ifndef ARDUINO

#endif
