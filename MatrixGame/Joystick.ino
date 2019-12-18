#include "Joystick.h"

static const byte pinJoystickSwitch = 8;
static const byte pinJoystickX = A0;
static const byte pinJoystickY = A1;

static const int averageValue = 512;
static const int threshold = 256;

Joystick::Joystick() { pinMode(pinJoystickSwitch, INPUT_PULLUP); }

void Joystick::read() {
  buttonState = digitalRead(pinJoystickSwitch);

  xValue = analogRead(pinJoystickX);
  yValue = 1024 - analogRead(pinJoystickY);
}

bool Joystick::isLeft() const { return xValue <= averageValue - threshold; }

bool Joystick::isRight() const { return xValue >= averageValue + threshold; }

bool Joystick::isDown() const { return yValue <= averageValue - threshold; }

bool Joystick::isUp() const { return yValue >= averageValue + threshold; }

bool Joystick::isPressed() const { return buttonState == LOW; }

int Joystick::getX() const { return xValue; }

int Joystick::getY() const { return yValue; }
