#pragma once

#include "Time.h"

/// Controls the time left of the game,
/// shown on a 4-digit 7-segment display.
class TimeDisplay {
  Time lastUpdateTime = 0;
  Time timeLeft = 0;
  bool paused = false;

 public:
  void pause();

  void unpause();

  bool isFinished() const;

  void increaseTimeLeft(Time extraTime);

  void increaseTimeLeftByDifficulty();

  void increaseTimeTo(Time totalTime);

  Time getTimeLeft() const;

  void update();

  void clear();

  void render() const;
};

extern TimeDisplay timeDisplay;
