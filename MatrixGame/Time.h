#pragma once

using Time = unsigned long;

extern Time updateTime;

bool debounce(bool value, Time& lastTime, Time delay = 500) {
  if (value && (updateTime - lastTime > delay)) {
    lastTime = updateTime;
    return true;
  }

  return false;
}

#include "Hardware.h"

class TimeDisplay {
  static const byte addr7DigitDisplay = 1;
  Time lastUpdateTime = 0;
  Time timeLeft = 0;

 public:
  void increaseTimeLeft(Time extraTime) {
    timeLeft += extraTime;
    lastUpdateTime = updateTime;
  }

  void increaseTimeTo(Time totalTime) {
    if (timeLeft < totalTime) {
      timeLeft = totalTime;
    }
    lastUpdateTime = updateTime;
  }

  void update() {
    Time timeDelta = updateTime - lastUpdateTime;
    lastUpdateTime = updateTime;
    if (timeLeft > timeDelta) {
      timeLeft -= timeDelta;
    } else {
      timeLeft = 0;
    }
  }

  void render() const {
    lc.setDigit(addr7DigitDisplay, 0, timeLeft / 10 % 10, false);
    lc.setDigit(addr7DigitDisplay, 1, timeLeft / 100 % 10, false);
    lc.setDigit(addr7DigitDisplay, 2, timeLeft / 1000 % 10, true);
    lc.setDigit(addr7DigitDisplay, 3, timeLeft / 10000 % 10, false);
  }
};

TimeDisplay timeDisplay;
