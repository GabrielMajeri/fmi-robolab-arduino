#include "TimeDisplay.h"

#include "Hardware.h"
#include "Settings.h"

const byte addr7DigitDisplay = 1;

void TimeDisplay::pause() {
  paused = true;
  lastUpdateTime = updateTime;
}

void TimeDisplay::unpause() {
  paused = false;
  lastUpdateTime = updateTime;
}

bool TimeDisplay::isFinished() const { return timeLeft == 0; }

void TimeDisplay::increaseTimeLeft(Time extraTime) {
  timeLeft += extraTime;
  lastUpdateTime = updateTime;
}

void TimeDisplay::increaseTimeLeftByDifficulty() {
  timeDisplay.increaseTimeLeft(getExtraTimeByDifficulty());
}

void TimeDisplay::increaseTimeTo(Time totalTime) {
  if (timeLeft < totalTime) {
    timeLeft = totalTime;
  }
  lastUpdateTime = updateTime;
}

Time TimeDisplay::getTimeLeft() const { return timeLeft; }

void TimeDisplay::update() {
  if (!paused) {
    Time timeDelta = updateTime - lastUpdateTime;
    if (timeLeft > timeDelta) {
      timeLeft -= timeDelta;
    } else {
      timeLeft = 0;
    }
  }

  lastUpdateTime = updateTime;
}

void TimeDisplay::clear() { lc.clearDisplay(addr7DigitDisplay); }

void TimeDisplay::render() const {
  lc.setDigit(addr7DigitDisplay, 0, timeLeft / 10 % 10, false);
  lc.setDigit(addr7DigitDisplay, 1, timeLeft / 100 % 10, false);
  lc.setDigit(addr7DigitDisplay, 2, timeLeft / 1000 % 10, true);
  lc.setDigit(addr7DigitDisplay, 3, timeLeft / 10000 % 10, false);
}
