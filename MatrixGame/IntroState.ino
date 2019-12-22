#include "IntroState.h"

const Time introDuration = 4000;

void IntroState::onBegin() {
  startTime = updateTime;

  lcd.clear();
  lcd.print("SANTA'S WORKSHOP");
  lcd.setCursor(0, 1);
  lcd.print("Merry Christmas!");
}

void IntroState::update() {
  // Enter the start menu after a fixed amount of time,
  // and allow the player to skip the intro sequence
  if (debounce(startTime, introDuration) || js.isPressedDebounced()) {
    setGameState(GameState::StartMenu);
  }
}
