#include "src/octocap.h"

void setup() {
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
	display.reset();
}

void loop() {
	animator.wait_for_frame();
	animator.tick();
	display.render();
	FastLED.show();
}

