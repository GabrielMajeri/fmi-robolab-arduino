#pragma once

#include "Modulo.h"
#include "State.h"

class StartMenuState : public State {
  Modulo<4> selectionIndex = 0;
  Time lastPressTime = 0;

 public:
  void onBegin() override { selectionIndex = 0; }

  void update() override {
    if (debounce(js.isLeft(), lastPressTime)) {
      --selectionIndex;
    } else if (debounce(js.isRight(), lastPressTime)) {
      ++selectionIndex;
    } else if (debounce(js.isPressed(), lastPressTime)) {
      switch (selectionIndex) {
        case 0:
          setGameState(GameState::Starting);
          break;
        case 1:
          setGameState(GameState::HighScoreMenu);
          break;
        case 2:
          setGameState(GameState::AboutMenu);
          break;
        case 3:
          setGameState(GameState::SettingsMenu);
          break;
      }
    }
  }

  void render() const override {
    lcd.setCursor(2, 0);
    lcd.print("Play!");

    lcd.setCursor(9, 0);
    lcd.print("About");

    lcd.setCursor(3, 1);
    lcd.print("Settings");

    if (selectionIndex == 0) {
      lcd.setCursor(1, 0);
    } else if (selectionIndex == 1) {
      lcd.setCursor(8, 0);
    } else if (selectionIndex == 2) {
      lcd.setCursor(2, 1);
    } else {
      lcd.setCursor(5, 1);
    }
    lcd.print('>');
  }
};
