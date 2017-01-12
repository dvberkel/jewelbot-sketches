#include <Arduino.h>

const unsigned int REST = 1;
const unsigned int TASK = 2;
const unsigned int BREAK = 3;
const unsigned int LONG_BREAK = 4;


const unsigned long MINUTES = 60 * 1000;
const unsigned long TASK_TIME = 25 * MINUTES;
const unsigned long BREAK_TIME = 5 * MINUTES;
const unsigned long LONG_BREAK_TIME = 15 * MINUTES;
const unsigned int  TASKS_BEFORE_LONG_BREAK = 4;

const ColorLabel BREAK_COLOR = RED;
const ColorLabel LONG_BREAK_COLOR = GREEN;

unsigned int state;
unsigned completed_tasks;
unsigned long start_time;

LED led;
Timer timer;
Buzzer buzzer;


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
}

void handle_task(void) {
  unsigned long now = timer.runtime_ms();
  if ((now - start_time) > TASK_TIME) {
    start_time = now;
    completed_tasks += 1;
    if (completed_tasks == TASKS_BEFORE_LONG_BREAK) {
      state = LONG_BREAK;
      buzzer.long_buzz();
      completed_tasks = 0;
    } else {
      state = BREAK;
      buzzer.short_buzz();
    }
  } else {
    led.turn_off_all();
  }
}

void handle_break(void) {
  unsigned long now = timer.runtime_ms();
  if ((now - start_time) > BREAK_TIME) {
    start_time = now;
    state = TASK;
  } else {
    led.turn_on_all(BREAK_COLOR);
  }
}

void handle_long_break(void) {
  unsigned long now = timer.runtime_ms();
  if ((now - start_time) > LONG_BREAK_TIME) {
    start_time = now;
    state = TASK;
  } else {
    led.turn_on_all(LONG_BREAK_COLOR);
  }
}

void button_press(void) {
  if (state == REST) {
    state = TASK;
    start_time = timer.runtime_ms();
  } else {
    // Do nothing
  }
}

void button_press_long(void) {
  reset();  
}

void reset(void) {
  state = REST;
  completed_tasks = 0;
}

