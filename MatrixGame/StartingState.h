#pragma once

#include "Map.h"
#include "Melody.h"
#include "State.h"
#include "Time.h"

const Time startUpTime = 5000;
const Time scrollDelayTime = 150;

class StartingState : public State {
  MelodyPlayer melody;
  Time lastScrollTime;

  void generateMap() {
    randomSeed(5);

    byte x = 4, y = 0, length = 5;

    levelMap.createPlatform(x, y, length);

    while (levelMap.hasSpaceForNewPlatform()) {
      levelMap.generatePlatform();
    }
  }

 public:
  void onBegin() override {
    melody.play();

    generateMap();

    currentView.centerOnX();
    currentView.moveToTop();
    lastScrollTime = updateTime;
  }

  void update() override {
    melody.update();

    if (updateTime - lastScrollTime >= scrollDelayTime) {
      currentView.moveDown();
      lastScrollTime = updateTime;
    }

    if (currentView.getY() == 0 && !melody.isPlaying()) {
      setGameState(GameState::Playing);
    }
  }

  void render() const override {
    lcd.setCursor(3, 0);
    lcd.print("Starting up");
    lcd.setCursor(3, 1);
    lcd.print("the game...");

    levelMap.render();
  }
};
