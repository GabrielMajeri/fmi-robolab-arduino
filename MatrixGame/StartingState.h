#pragma once

#include "Map.h"
#include "Melody.h"
#include "State.h"
#include "Time.h"

const Time startUpTime = 5000;
const Time scrollDelayTime = 150;

class StartingState : public State {
  Time lastScrollTime;

  void generateInitialMap();

 public:
  void onBegin() override {
    melodyPlayer.setMelody(jingleBellsMelody);
    melodyPlayer.play();

    generateInitialMap();

    currentView.centerOnX();
    currentView.moveToTop();
    lastScrollTime = updateTime;

    timeDisplay.pause();
  }

  void update() override {
    melodyPlayer.update();

    timeDisplay.increaseTimeLeft(130);

    if (updateTime - lastScrollTime >= scrollDelayTime) {
      currentView.moveDown();
      lastScrollTime = updateTime;
    }

    if (js.isPressed() ||
        currentView.getY() == 0 && !melodyPlayer.isPlaying()) {
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
