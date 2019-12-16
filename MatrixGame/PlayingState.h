#pragma once

#include "Map.h"
#include "Player.h"
#include "State.h"

class PlayingState : public State {
  unsigned score = 0;

 public:
  void onBegin() override {}

  void update() override {
    player.update();

    if (player.getRelativeX() > 4) {
      currentView.moveRight();
    }

    if (player.getRelativeX() < 3) {
      currentView.moveLeft();
    }

    if (player.getRelativeY() > 4) {
      currentView.moveUp();
    }

    if (player.getRelativeY() < 3) {
      currentView.moveDown();
    }

    if (player.getY() > 10) {
      player.shiftDown();
      levelMap.shiftDown();
    }

    if (levelMap.hasSpaceForNewPlatform()) {
      levelMap.generatePlatform();
    }
  }

  void render() const override { levelMap.render(); }
};
