#ifndef MISTRESS_SYSTEM_H
#define MISTRESS_SYSTEM_H

#ifdef ARDUINO
#include <FastLED.h>
#else

#include <cstdint>
#include <cstdlib>
#include <time.h>
#include <ostream>
#include <cmath>

extern timespec boot_ts;

using u8 = std::uint8_t;

template<typename T>
static inline T abs(T v)
{
	return v < T{0} ? -v : v;
}

template<typename T>
static inline T min(T a, T b)
{
	return a < b ? a : b;
}

template<typename T>
static inline T max(T a, T b)
{
	return a >= b ? a : b;
}

template<typename T>
static inline T mod(T a, T b)
{ }

template<>
inline int mod<int>(int a, int b)
{
    return a % b;
}

template<>
inline float mod<float>(float a, float b)
{
    return fmod(a, b);
}

static inline int random(int n)
{
	return mod(rand(), n);
}

static inline int random(int n, int x)
{
	return mod(rand(), (x - n)) + n;
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

    friend std::ostream & operator << (std::ostream & os, CHSV const & obj)
    {
        os << "hsv{" << static_cast<int>(obj.h) << ", " << static_cast<int>(obj.s) << ", " << static_cast<int>(obj.v) << "}      ";
        return os;
    }
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
        float ht = float(hsv.h) / 255.0f * 6.0f;
		float s = hsv.s / 255.0f;
		float v = hsv.v / 255.0f;

		float c = v * s;
		float x = c * (1.0f - abs(mod(ht, 2.0f) - 1.0f));
		float m = v - c;

		float fr = 0, fg = 0, fb = 0;
		if (ht < 1.0f)
			{ fr = c; fg = x; fb = 0; }
        else if (ht < 2.0f)
			{ fr = x; fg = c; fb = 0; }
        else if (ht < 3.0f)
			{ fr = 0; fg = c; fb = x; }
        else if (ht < 4.0f)
			{ fr = 0; fg = x; fb = c; }
        else if (ht < 5.0f)
			{ fr = x; fg = 0; fb = c; }
        else
			{ fr = c; fg = 0; fb = x; }

		r = (fr + m) * 255.0f;
		g = (fg + m) * 255.0f;
		b = (fb + m) * 255.0f;
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

    friend std::ostream & operator << (std::ostream & os, CRGB const & obj)
    {
        os << "rgb{" << static_cast<int>(obj.r) << ", " << static_cast<int>(obj.g) << ", " << static_cast<int>(obj.b) << "}      ";
        return os;
    }
};

#endif // #ifndef ARDUINO

CHSV makeRandomColor();
CHSV makeRandomColor(CHSV inContrastTo);

#endif

