#pragma once

#include "Map.h"
#include "Player.h"
#include "Settings.h"
#include "State.h"

class PlayingState : public State {
  bool paused, playerMoved, playerDied;
  Time dieTime;

  bool isGameOver() const;

 public:
  void onBegin() override;
  void onEnd() override;

  void update() override;

  void render() const override;
};
