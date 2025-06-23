# Mistress

I will wear this cephalopod like a hat.

## Building

This uses [Pyke](https://github.com/spacemeat/pyke) to build on the PC, and the Arduino IDE to build for a board. You can adjust the parameters in [octocap.h](./octocap.h) to fit the line lengths. The sketch maintains the entire frame buffer for all LEDs, so you'll need that much free memory on the board.

Currently builds for desktop Linux, and whichever boards fit the bill. C++ 20, with Arduino/ESP32 foo. On desktop, having a 24-bit capable color terminal will visualize the LED animations without the need for a controller.

Squish.
