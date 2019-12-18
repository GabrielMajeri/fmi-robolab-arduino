#pragma once

#include "Map.h"
#include "Score.h"
#include "State.h"

const Time scoreDisplayDelay = 5000;

class GameOverState : public State {
  Time startTime, jsPressTime;
  bool displayScore;

 public:
  void onBegin() override {
    startTime = updateTime;
    displayScore = true;
  }

  void update() override {
    if (updateTime - startTime > scoreDisplayDelay) {
      displayScore = false;
    }

    if (debounce(js.isPressed(), jsPressTime, 1000)) {
      if (displayScore) {
        displayScore = false;
      } else {
        setGameState(GameState::StartMenu);
      }
    }
  }

  void render() const;
};
