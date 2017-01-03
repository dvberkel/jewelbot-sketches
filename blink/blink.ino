#include <Arduino.h>

LED led;
Timer timer;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  led.turn_on_single(NW, BLUE);
  timer.pause(500);
  led.turn_off_single(NW);
  timer.pause(500); 
}
