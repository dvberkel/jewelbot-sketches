#include <Arduino.h>

const unsigned int REST = 1;
const unsigned int TASK = 2;
const unsigned int BREAK = 3;
const unsigned int LONG_BREAK = 4;


const unsigned long MINUTES = 500; // 60 * 1000;
const unsigned long TASK_TIME = 25 * MINUTES;
const unsigned long BREAK_TIME = 5 * MINUTES;
const unsigned long LONG_BREAK_TIME = 15 * MINUTES;

unsigned int state;
unsigned checkmarks;
unsigned long start_time;

LED led;


void setup() {
  reset();
}

void loop() {
  pomodore();
}

void pomodore(void) {
  switch (state) {
    case REST:
    handle_rest();
    break;

    case TASK:
    handle_task();
    break;

    case BREAK:
    handle_break();
    break;

    case LONG_BREAK:
    handle_long_break();
    break;
  }
}

void handle_rest(void) {
  // Wait for a button press
  led.turn_off_all();
}

void handle_task(void) {
  unsigned long now = millis();
  if ((now - start_time) > TASK_TIME) {
    start_time = now;
    checkmarks += 1;
    if (checkmarks == 4) {
      state = LONG_BREAK;
      checkmarks = 0;
    } else {
      state = BREAK;
    }
  } else {
    led.turn_off_all();
  }
}

void handle_break(void) {
  unsigned long now = millis();
  if ((now - start_time) > BREAK_TIME) {
    start_time = now;
    state = TASK;
  } else {
    led.turn_on_all(RED);
  }
}

void handle_long_break(void) {
  unsigned long now = millis();
  if ((now - start_time) > LONG_BREAK_TIME) {
    start_time = now;
    state = TASK;
  } else {
    led.turn_on_all(GREEN);
  }
}

void button_press(void) {
  if (state == REST) {
    state = TASK;
    start_time = millis();
  } else {
    // Do nothing
  }
}

void button_press_long(void) {
  reset();  
}

void reset(void) {
  state = REST;
  checkmarks = 0;
}

