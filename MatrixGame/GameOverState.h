#pragma once

#include "Map.h"
#include "Score.h"
#include "State.h"

/// Screen displayed once the player finishes the game (i.e. dies).
class GameOverState : public State {
  Time lastTime;
  bool printingScore, printingHighScore;

  void printScore();
  void printHighScore();
  void printReturnToMenu();

 public:
  void onBegin() override;
  void onEnd() override;

  void update() override;
};
