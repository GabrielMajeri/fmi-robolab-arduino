#include "Time.h"

#include "Hardware.h"
#include "Settings.h"

// On easier difficulties, each gift gives less extra time,
// but they are more common.
const Time extraTimeEasy = 2000;
const Time extraTimeMedium = 3500;
const Time extraTimeHard = 5000;

const byte addr7DigitDisplay = 1;

bool debounce(bool value, Time& lastTime, Time delay) {
  if (value && (updateTime - lastTime > delay)) {
    lastTime = updateTime;
    return true;
  }

  return false;
}

void TimeDisplay::increaseTimeLeft(Time extraTime) {
  timeLeft += extraTime;
  lastUpdateTime = updateTime;
}

void TimeDisplay::increaseTimeLeftByDifficulty() {
  switch (settings.difficulty) {
    case Difficulty::Easy:
      timeDisplay.increaseTimeLeft(extraTimeEasy);
      break;
    case Difficulty::Medium:
      timeDisplay.increaseTimeLeft(extraTimeMedium);
      break;
    case Difficulty::Hard:
      timeDisplay.increaseTimeLeft(extraTimeHard);
      break;
  }
}

void TimeDisplay::render() const {
  lc.setDigit(addr7DigitDisplay, 0, timeLeft / 10 % 10, false);
  lc.setDigit(addr7DigitDisplay, 1, timeLeft / 100 % 10, false);
  lc.setDigit(addr7DigitDisplay, 2, timeLeft / 1000 % 10, true);
  lc.setDigit(addr7DigitDisplay, 3, timeLeft / 10000 % 10, false);
}
