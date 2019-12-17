#pragma once

#include "Map.h"
#include "Melody.h"
#include "State.h"
#include "Time.h"

const Time startUpTime = 5000;
const Time scrollDelayTime = 150;

class StartingState : public State {
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
    melodyPlayer.setMelody(jingleBellsMelody);
    melodyPlayer.play();

    generateMap();

    currentView.centerOnX();
    currentView.moveToTop();
    lastScrollTime = updateTime;
  }

  void update() override {
    melodyPlayer.update();

    timeDisplay.increaseTimeLeft(130);

    if (updateTime - lastScrollTime >= scrollDelayTime) {
      currentView.moveDown();
      lastScrollTime = updateTime;
    }

    if (currentView.getY() == 0 && !melodyPlayer.isPlaying()) {
      timeDisplay.increaseTimeTo(30000);
      setGameState(GameState::Playing);
    }
  }

  void render() const override {
    lcd.setCursor(3, 0);
    lcd.print("Starting up");
    lcd.setCursor(3, 1);
    lcd.print("the game...");

    levelMap.render();
    timeDisplay.render();
  }
};
