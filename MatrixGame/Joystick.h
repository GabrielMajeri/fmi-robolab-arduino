#pragma once

#include "Time.h"

class Joystick {
  Time lastCheckTime;
  int xValue = 0, yValue = 0;
  bool buttonState = HIGH;

 public:
  Joystick();

  void read();

  bool isLeft() const;
  bool isRight() const;
  bool isDown() const;
  bool isUp() const;

  bool isPressed() const;

  bool isLeftDebounced();
  bool isRightDebounced();
  bool isDownDebounced();
  bool isUpDebounced();

  bool isPressedDebounced();

  int getX() const;
  int getY() const;
};
