#include "Joystick.h"

static const byte PIN_JS_SW = 8;
static const byte PIN_JS_X = A0;
static const byte PIN_JS_Y = A1;

static const int AVG_VALUE = 512;
static const int THRESHOLD = 256;

static const int LEFT_THRESH = AVG_VALUE - THRESHOLD;
static const int RIGHT_THRESH = AVG_VALUE + THRESHOLD;
static const int UP_THRESH = AVG_VALUE - THRESHOLD;
static const int DOWN_THRESH = AVG_VALUE + THRESHOLD;

Joystick::Joystick() { pinMode(PIN_JS_SW, INPUT_PULLUP); }

void Joystick::read() {
  buttonState = digitalRead(PIN_JS_SW);

  xValue = analogRead(PIN_JS_X);
  yValue = 1024 - analogRead(PIN_JS_Y);

  movedRight = (prevXValue > LEFT_THRESH) && (xValue <= LEFT_THRESH);
  movedLeft = (prevXValue < RIGHT_THRESH) && (xValue >= RIGHT_THRESH);
  movedDown = (prevYValue > UP_THRESH) && (yValue <= UP_THRESH);
  movedUp = (prevYValue < DOWN_THRESH) && (yValue >= DOWN_THRESH);

  prevXValue = xValue;
  prevYValue = yValue;
}

bool Joystick::isMoveLeft() const { return movedLeft; }

bool Joystick::isMoveRight() const { return movedRight; }

bool Joystick::isMoveDown() const { return movedDown; }

bool Joystick::isMoveUp() const { return movedUp; }

bool Joystick::isPressed() const { return buttonState == LOW; }

int Joystick::getX() const { return xValue; }

int Joystick::getY() const { return yValue; }
