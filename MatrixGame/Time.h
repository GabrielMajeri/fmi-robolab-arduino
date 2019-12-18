#pragma once

using Time = unsigned long;

extern Time updateTime;

bool debounce(bool value, Time& lastTime, Time delay = 500);

class TimeDisplay {
  Time lastUpdateTime = 0;
  Time timeLeft = 0;
  bool paused = false;

 public:
  void pause() {
    paused = true;
    lastUpdateTime = updateTime;
  }

  void unpause() {
    paused = false;
    lastUpdateTime = updateTime;
  }

  bool isFinished() const { return timeLeft == 0; }

  void increaseTimeLeft(Time extraTime);

  void increaseTimeLeftByDifficulty();

  void increaseTimeTo(Time totalTime) {
    if (timeLeft < totalTime) {
      timeLeft = totalTime;
    }
    lastUpdateTime = updateTime;
  }

  void update() {
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

  void render() const;
};

TimeDisplay timeDisplay;
