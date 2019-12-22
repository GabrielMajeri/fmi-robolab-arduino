#include "StartingState.h"

#include "MelodyPlayer.h"
#include "Player.h"
#include "Settings.h"

const Time startUpTime = 5000;
const Time scrollDelayTime = 150;

const byte pinNotConnected = A5;

void StartingState::generateInitialMap() {
  randomSeed(analogRead(pinNotConnected));

  byte x = 4, y = 0, length = 5;

  levelMap.createPlatform(x, y, length);

  while (levelMap.hasSpaceForNewPlatform()) {
    levelMap.generatePlatform();
  }
}

void StartingState::onBegin() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Starting up");
  lcd.setCursor(3, 1);
  lcd.print("the game...");

  melodyPlayer.setMelody(jingleBellsMelody);
  melodyPlayer.play();

  generateInitialMap();

  currentView.centerOnX();
  currentView.moveToTop();
  lastScrollTime = updateTime;

  timeDisplay.pause();

  player.reset();
}

void StartingState::update() {
  melodyPlayer.update();

  if (debounce(lastScrollTime, scrollDelayTime)) {
    currentView.moveDown();
    lastScrollTime = updateTime;
  }

  if (js.isPressed() ||
      (currentView.getY() == 0) && !melodyPlayer.isPlaying()) {
    timeDisplay.increaseTimeTo(getStartingTimeByDifficulty());
    setGameState(GameState::Playing);
  }
}

void StartingState::render() const {
  levelMap.render();
  timeDisplay.render();
}
