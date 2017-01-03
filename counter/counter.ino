#include <Arduino.h>

LED led;
Timer timer;

const int BASE = 2;
const int NUMBER_OF_BITS = 4;
const LED_Pos leds[] = {SW, NW, NE, SE};
const ColorLabel colors[] = {WHITE, GREEN};

int bits[4];

void setup() {
  reset(bits);
}

void loop() {
  light_up(bits);
}

void light_up(int bits[]) {
  for (int index = 0; index < NUMBER_OF_BITS; index++) {
    if (bits[index] > 0) {
      led.turn_on_single(leds[index], colors[bits[index]]);
    } else {
      led.turn_off_single(leds[index]);
    }
  }  
}

void button_press(void) {
  increment(bits);
}

void increment(int bits[]) {
  int carry = 1;
  for (int index = 0; index < NUMBER_OF_BITS; index++) {
    bits[index] = bits[index] + carry;
    if (bits[index] >= BASE) {
      bits[index] = 0;
      carry = 1;
    } else {
      carry = 0;
    }
  }
}

void button_press_long(void) {
  reset(bits);
}

void reset(int bits[]) {
  for (int index = 0; index < NUMBER_OF_BITS; index++) {
    bits[index] = 0;
  }
}

