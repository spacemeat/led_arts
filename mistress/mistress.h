#ifdef ARDUINO
#include <FastLED.h>
const int LED_PIN = 5;
#else
#include <iostream>
#include <iomanip>
#include "system.h"
#endif

// Hardware setup

const long NumTracks = 6;
const long NumStripsPerTrack = 1;
const long NumLedsPerStrip = 150;
const long NumLedsPerTrack = NumStripsPerTrack * NumLedsPerStrip;
const long NumRocketsPerTrack = 2;
const long NumSplashesPerTrack = NumRocketsPerTrack * NumTracks;

const unsigned char max_power = 255;

const long FramePeriod = 1024 / 30;

extern CRGB frame_buffer[NumTracks * NumLedsPerTrack];

// Data classes

struct Splash
{
	Splash();
	void set();
	void reset();
	void animate(long ticks);
	void render();

	bool _active;
	int _track_id;
	long _pos;
	long _prev_pos;
	int _vel;
	int _acc;
	CHSV _hsv;
};

struct Rocket
{
	Rocket();
	void set_splashes(Splash ** splashePtrs);
	void set();
	void reset();
	void animate(long ticks);
	void render();

	int _track_id;
	Splash ** _splash_ptrs;
	long _time_to_start;
	long _pos;
	long _prev_pos;
	int _vel;
	int _acc;
	CHSV _max_hsv;
	CHSV _current_hsv;
	CHSV _init_hsv;
};

#ifndef ARDUINO
std::ostream & operator << (std::ostream & os, Rocket const & rhs);
#endif

struct Track
{
	Track();
	void set_track_id(int track_id);
	void set_splashes(Splash ** splashes);
	void set();
	void reset();
	void animate(long ticks);
	void render();

	int _track_id;
	Rocket _rockets[NumRocketsPerTrack];
	Splash _splashes[NumSplashesPerTrack];
};

struct Display
{
	Display();
	void set();
	void reset();
	void animate(long ticks);
	void render();

	Track _tracks[NumTracks];
	Splash * _splashePtrs[NumSplashesPerTrack * NumTracks];
};

extern Display display;

// Animator

class Animator
{
public:
	Animator();
	void wait_for_frame();
	void tick();

	long get_time() { return _time; }
	long get_prev_time() { return _prev_time; }

private:
	long _time = 0;
	long _prev_time = 0;
};

extern Animator animator;
