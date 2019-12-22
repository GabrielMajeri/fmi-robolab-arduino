#pragma once

#include "Map.h"
#include "Player.h"
#include "Settings.h"
#include "State.h"

/// State with actual gameplay, in which the player can
/// move and jump around the map.
class PlayingState : public State {
  bool paused, playerMoved, playerDied;
  Difficulty savedDifficulty;
  Time dieTime;

  bool isGameOver() const;

 public:
  void onBegin() override;
  void onEnd() override;

  void update() override;

  void render() const override;
};
