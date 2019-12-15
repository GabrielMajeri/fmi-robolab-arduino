#pragma once

class State {
 public:
  virtual void onBegin() {}
  virtual void onEnd() {}

  virtual void update() = 0;
  virtual void render() = 0;
};

enum class GameState {
  StartMenu,
  SettingsMenu,
  AboutMenu,
  Starting,
  Playing,
  GameOver,
};

extern GameState currentState;
