#include  <Arduino.h>

LED led;
const int NUMBER_OF_COLORS = 4;
const ColorLabel colors[] = {RED, GREEN, BLUE, WHITE};

int counter = 0;

void setup() {
  counter = 0; 
}

void loop() {
  color();
}

void button_press(void) {
  increment();
}

void increment(void) {
  counter = counter + 1;
  if (counter >= 2*NUMBER_OF_COLORS) {
    counter = 0;
  }
}

void color(void) {
  if (counter % 2 == 1) {
    led.turn_off_all();
  } else {
    int index = counter / 2;
    ColorLabel current = colors[index];
    led.turn_on_all(current);
  }
}

