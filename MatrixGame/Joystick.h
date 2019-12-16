#pragma once

class Joystick {
  bool buttonState = HIGH;
  int xValue = 0, yValue = 0;

 public:
  Joystick();

  void read();

  bool isLeft() const;
  bool isRight() const;
  bool isDown() const;
  bool isUp() const;

  bool isPressed() const;

  int getX() const;
  int getY() const;
};
