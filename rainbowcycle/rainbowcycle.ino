#include <Arduino.h>

LED led;

const int NUMBER_OF_LEDS = 4;
const LED_Pos leds[] = {SW, NW, NE, SE};
const ColorLabel colors[] = {RED, YELLOW, GREEN, BLUE};

int offset;

void setup() {
  offset = 0;
}

void loop() {
  color();
}

void button_press(void) {
  increment();
}

void increment(void) {
  offset = offset + 1;
  if (offset >= NUMBER_OF_LEDS) {
    offset = 0;
  }
}

void color(void) {
  for (int current = 0; current < NUMBER_OF_LEDS; current++) {
    int index = (current + offset) % NUMBER_OF_LEDS;
    LED_Pos ledPosition = leds[index];
    ColorLabel colorLabel = colors[index];
    led.turn_on_single(ledPosition, colorLabel);
  }
}

