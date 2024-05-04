#include "mistress.h"

void setup() {
	FastLED.addLeds<WS2811, LED_PIN>(frame_buffer, NumTracks * NumLedsPerTrack);
	display.set();
}

void loop() {
	animator.wait_for_frame();
	animator.tick();
	display.render();
	FastLED.show();
}
