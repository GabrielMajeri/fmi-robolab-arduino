#pragma once

#include "Hardware.h"
#include "Melody.h"
#include "Time.h"

class State {
 public:
  virtual void onBegin() {}
  virtual void onEnd() {}

  virtual void update() = 0;
  virtual void render() const = 0;
};

enum class GameState {
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
