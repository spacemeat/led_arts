#ifdef ARDUINO
#include <FastLED.h>

const int LED_S1 = 13;
const int LED_S2 = 27;
const int LED_S3 = 26;
const int LED_S4 = 25;
const int LED_S5 = 33;
const int LED_S6 = 32;
const int LED_S7 = ??;
const int LED_S8 = ??;

#else
#include <iostream>
#include <iomanip>
#include "system.h"
#endif


/* For DOIT ESP32 DEVKIT V1   (ESP32-VROOM-32D 30-pin layout)
 * TODO: Rejigger this for 38-pin ESP32
 * EN
 * SENSOR VP
 * SENSOR VN
 * 34
 * 35
 * 32  - strip 6
 * 33  - strip 5
 * 25  - strip 4
 * 26  - strip 3
 * 27  - strip 2
 * 14
 * 12
 * 13  - strip 1
 * GND - ground to board
 * 5V  - 5V to src
*/

// Hardware setup

const long NumBands = 20;
const long NumLedsPerBand = 20;
const long NumLedsInMantle = NumBands * NumLedsPerBand;

const long NumTentacles = 8;
const long NumStripsPerTentacle = 1;
const long NumLedsPerStrip = 60;
const long NumLedsPerTentacle = NumStripsPerTentacle * NumLedsPerStrip;
const long NumLedsInTentacles = NumTentacles * NumLedsPerTentacle;

const unsigned char max_power = 255;

const long FramePeriodInMs = 1024 / 32;

extern CRGB frame_buffer[NumLedsInMantle + NumLedsInTentacles];

// Data classes

#ifndef ARDUINO
#endif

struct Tentacle
{
	Tentacle();
	void set_tentacle_id(int tentacle_id);
	void set();
	void reset();
	void animate(long ticks);
	void render();

	int _tentacle_id;
};

struct MantleBand
{
    MantleBand();
	void set_band_id(int band_id);
	void set();
	void reset();
	void animate(long ticks);
	void render();

    int _band_id;
};

class Effect;

struct Octopus
{
    Octopus();
	void set();
	void reset();
	void animate(long ticks);
	void render();

    MantleBand _mantleBands[NumBands];
	Tentacle _tentacles[NumTentacles];
    Effect * _previousEffect;
    Effect * _currentEffect;
};

struct Display
{
	Display();
	void set();
	void reset();
	void animate(long ticks);
	void render();

    Octopus _octopus;
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

