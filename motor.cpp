#include "motor.h"
#include <Arduino.h>

#define Aa 7 //motor pins
#define Ab 5
#define Ba 8
#define Bb 6
#define SPEED 120

// here i made predefined ranges for the angles and what directions, i realise i could have actually mapped the angle again from 0-90 degrees to and 0-100, 
//and instead of having all these different functions have a single one with the integer would have made the movement very smooth. damn i wish i did that now

void Motor::RIGHT() {
  move(1, 25, 1, SPEED);
}

void Motor::FRR() {
  move(1, 40, 1, SPEED);
}

void Motor::FFR() {
  move(1, 60, 1, SPEED);
}

void Motor::FWD() {
  move(1, SPEED, 1, SPEED);
}

void Motor::FFL() {
  move(1, SPEED, 1, 60);
}

void Motor::FLL() {
  move(1, SPEED, 1, 40);
}

void Motor::LEFT() {
  move(1, SPEED, 1, 25);
}

void Motor::stop() {
  move(1, 0, 1, 0);
}

void Motor::back() {
  move(0, SPEED, 0, SPEED);
}

void Motor::init() {
  for (int i = 6; i < 9; i++) {
    pinMode(i, OUTPUT);
  }
}

void Motor::move(bool a, int b, bool c, int d) {
  digitalWrite(Aa, a);
  digitalWrite(Ba, c);
  analogWrite(Ab, b);
  analogWrite(Bb, d);
}
