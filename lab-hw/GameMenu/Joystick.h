#ifndef JOYSTICK_H
#define JOYSTICK_H

class Joystick {
  static const byte JS_PIN_X = A0;
  static const byte JS_PIN_Y = A1;
  static const byte JS_PIN_SW = 0;

  static const int THRESHOLD = 256;
  static const long DEBOUNCE_TIME = 500;

  int xValue = 0, yValue = 0;
  bool swState = HIGH;
  bool movedLeft = false, movedRight = false,
    movedUp = false, movedDown = false;

  long lastPressTime = 0;

public:
  void init() {
    pinMode(JS_PIN_SW, INPUT_PULLUP);
  }

  void read() {
    xValue = analogRead(JS_PIN_X);
    yValue = analogRead(JS_PIN_Y);
    swState = digitalRead(JS_PIN_SW);
  }

  bool isMovedLeft() {
    bool ok = false;
    if (yValue < 512 - THRESHOLD) {
      if (!movedLeft) {
        ok = true;
      }
      movedLeft = true;
    } else {
      movedLeft = false;
    }

    return ok;
  }

  bool isMovedRight() {
    bool ok = false;
    if (yValue > 512 + THRESHOLD) {
      if (!movedRight) {
        ok = true;
      }
      movedRight = true;
    } else {
      movedRight = false;
    }
    return ok;
  }

  bool isMovedUp() {
    bool ok = false;
    if (xValue > 512 + THRESHOLD) {
      if (!movedUp) {
        ok = true;
      }
      movedUp = true;
    } else {
      movedUp = false;
    }
    return ok;
  }

  bool isMovedDown() {
    bool ok = false;
    if (xValue < 512 - THRESHOLD) {
      if (!movedDown) {
        ok = true;
      }
      movedDown = true;
    } else {
      movedDown = false;
    }
    return ok;
  }

  bool isPressed() {
    bool ok = false;
    if (swState == LOW) {
      if (millis() - lastPressTime > DEBOUNCE_TIME) {
        ok = true;
      }
      lastPressTime = millis();
    }
    return ok;
  }

  void printDebugInfo() const {
    Serial.print("X: ");
    Serial.print(xValue);
    Serial.print(" | ");

    Serial.print("Y: ");
    Serial.print(yValue);
    Serial.print(" | ");

    Serial.print("SW: ");
    Serial.print(swState);
    Serial.println();
  }
};

#endif
