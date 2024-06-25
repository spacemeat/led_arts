#include "mistress.h"

void setup() {
	pinMode(LED_S1, OUTPUT);
	pinMode(LED_S2, OUTPUT);
	pinMode(LED_S3, OUTPUT);
	pinMode(LED_S4, OUTPUT);
	pinMode(LED_S5, OUTPUT);
	pinMode(LED_S6, OUTPUT);

	FastLED.addLeds<WS2811, LED_S1, GRB>(frame_buffer + NumLedsPerTrack * 0, NumLedsPerTrack);
	FastLED.addLeds<WS2811, LED_S2, GRB>(frame_buffer + NumLedsPerTrack * 1, NumLedsPerTrack);
	FastLED.addLeds<WS2811, LED_S3, GRB>(frame_buffer + NumLedsPerTrack * 2, NumLedsPerTrack);
	FastLED.addLeds<WS2811, LED_S4, GRB>(frame_buffer + NumLedsPerTrack * 3, NumLedsPerTrack);
	FastLED.addLeds<WS2811, LED_S5, GRB>(frame_buffer + NumLedsPerTrack * 4, NumLedsPerTrack);
	FastLED.addLeds<WS2811, LED_S6, GRB>(frame_buffer + NumLedsPerTrack * 5, NumLedsPerTrack);
	display.set();
}

void loop() {
	animator.wait_for_frame();
	animator.tick();
	display.render();
	FastLED.show();
}
