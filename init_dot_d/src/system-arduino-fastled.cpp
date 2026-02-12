#ifndef ARDUINO
#error This code unit must be compiled in an ARDUINO environment.
#endif

#include <FastLED.h>

const int LED_S1 = 13;
const int LED_S2 = 27;
const int LED_S3 = 26;
const int LED_S4 = 25;
const int LED_S5 = 33;
const int LED_S6 = 32;
const int LED_S7 = 23;
const int LED_S8 = 12;

/* For DOIT ESP32 DEVKIT V1   (ESP32-VROOM-32D 30-pin layout)
 * EN
 * SENSOR VP
 * SENSOR VN
 * 34  - strip 8
 * 36  - strip 7
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


void setup_hardware()
{
    // TODO: Setup serial if we want

	pinMode(LED_S1, OUTPUT);
	pinMode(LED_S2, OUTPUT);
	pinMode(LED_S3, OUTPUT);
	pinMode(LED_S4, OUTPUT);
	pinMode(LED_S5, OUTPUT);
	pinMode(LED_S6, OUTPUT);
	pinMode(LED_S7, OUTPUT);
	pinMode(LED_S8, OUTPUT);

	FastLED.addLeds<WS2812B, LED_S1, GRB>(frame_buffer + NumLedsPerTentacle * 0, NumLedsPerTentacle);
	FastLED.addLeds<WS2812B, LED_S2, GRB>(frame_buffer + NumLedsPerTentacle * 1, NumLedsPerTentacle);
	FastLED.addLeds<WS2812B, LED_S3, GRB>(frame_buffer + NumLedsPerTentacle * 2, NumLedsPerTentacle);
	FastLED.addLeds<WS2812B, LED_S4, GRB>(frame_buffer + NumLedsPerTentacle * 3, NumLedsPerTentacle);
	FastLED.addLeds<WS2812B, LED_S5, GRB>(frame_buffer + NumLedsPerTentacle * 4, NumLedsPerTentacle);
	FastLED.addLeds<WS2812B, LED_S6, GRB>(frame_buffer + NumLedsPerTentacle * 5, NumLedsPerTentacle);
	FastLED.addLeds<WS2812B, LED_S7, GRB>(frame_buffer + NumLedsPerTentacle * 6, NumLedsPerTentacle);
	FastLED.addLeds<WS2812B, LED_S8, GRB>(frame_buffer + NumLedsPerTentacle * 7, NumLedsPerTentacle);
}

void present()
{
    FastLED.show();
}

