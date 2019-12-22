#pragma once

#include "Hardware.h"
#include "Melody.h"
#include "Time.h"

class State {
 public:
  virtual void onBegin() {}
  virtual void onEnd() {}

  virtual void update() {}
  virtual void render() const {}
};

enum class GameState {
  Intro,
  StartMenu,
  HighScoreMenu,
  AboutMenu,
  SettingsMenu,
  Starting,
  Playing,
  GameOver,
};

State& getGameState();
void setGameState(GameState newState);
