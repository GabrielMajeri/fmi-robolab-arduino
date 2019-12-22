#include "StartMenuState.h"

const byte startMenuItems = 4;

void StartMenuState::printMenuLabels() const {
  lcd.setCursor(2, 0);
  lcd.print("Play!");

  lcd.setCursor(8, 0);
  lcd.print("HiScores");

  lcd.setCursor(1, 1);
  lcd.print("About");

  lcd.setCursor(7, 1);
  lcd.print("Settings");
}

void StartMenuState::printSelectionArrow() const {
  if (selectionIndex == 0) {
    lcd.setCursor(1, 0);
  } else if (selectionIndex == 1) {
    lcd.setCursor(7, 0);
  } else if (selectionIndex == 2) {
    lcd.setCursor(0, 1);
  } else {
    lcd.setCursor(6, 1);
  }
  lcd.print('>');
}

void StartMenuState::onBegin() { selectionIndex = 0; }

void StartMenuState::update() {
  if (js.isLeftDebounced()) {
    selectionIndex = (selectionIndex + startMenuItems - 1) % startMenuItems;
  }
  if (js.isRightDebounced()) {
    selectionIndex = (selectionIndex + 1) % startMenuItems;
  }
  if (js.isUpDebounced()) {
    selectionIndex = (selectionIndex + startMenuItems - 2) % startMenuItems;
  }
  if (js.isDownDebounced()) {
    selectionIndex = (selectionIndex + startMenuItems + 2) % startMenuItems;
  }

  if (js.isPressedDebounced()) {
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

void StartMenuState::render() const {
  lcd.clear();
  printMenuLabels();
  printSelectionArrow();
}
