#pragma once

#include "Map.h"
#include "Player.h"
#include "Settings.h"
#include "State.h"

class PlayingState : public State {
  bool playerMoved, playerDied;
  Time dieTime;

  bool isGameOver() const;

 public:
  void onBegin() override;

  void update() override;

  void render() const override;
};
