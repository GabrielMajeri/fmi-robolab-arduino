#pragma once

class Joystick {
  bool buttonState = HIGH;
  int xValue = 0, prevXValue = 0;
  int yValue = 0, prevYValue = 0;

  bool movedLeft = false;
  bool movedRight = false;
  bool movedUp = false;
  bool movedDown = false;

 public:
  Joystick();

  void read();

  bool isMoveLeft() const;
  bool isMoveRight() const;
  bool isMoveDown() const;
  bool isMoveUp() const;

  bool isPressed() const;

  int getX() const;
  int getY() const;
};
