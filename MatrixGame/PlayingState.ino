#include "PlayingState.h"

#include "Map.h"
#include "Player.h"
#include "Score.h"
#include "TimeDisplay.h"

const Time deathDelay = 2000;

bool PlayingState::isGameOver() const {
  return player.hasNoLivesLeft() || timeDisplay.isFinished();
}

void PlayingState::onBegin() {
  savedDifficulty = getCurrentDifficulty();

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Use JS to move.");
  lcd.setCursor(0, 1);
  lcd.print("Press for pause.");

  melodyPlayer.setMelody(tetrisMelody);
  melodyPlayer.play();

  player.moveTo(6, 1);
  player.setLives(getStartingLivesByDifficulty());

  timeDisplay.pause();

  paused = false;
  playerMoved = false;
  playerDied = false;
}

void PlayingState::onEnd() {
  melodyPlayer.stop();

  if (timeDisplay.getTimeLeft() > 0) {
    score.addPointsForTimeLeft(timeDisplay.getTimeLeft() / 1000);
  }

  if (player.getLives() > 0) {
    score.addPointsForLivesLeft(player.getLives());
  }

  if (score.isHighScore()) {
    score.updateHighScoreList();
  }

  timeDisplay.clear();

  setCurrentDifficulty(savedDifficulty);
  player.reset();
}

void PlayingState::update() {
  if (isGameOver()) {
    setGameState(GameState::GameOver);
  }

  if (js.isPressedDebounced()) {
    paused = !paused;
  }

  if (paused) {
    return;
  }

  timeDisplay.update();
  melodyPlayer.update();
  if (!melodyPlayer.isPlaying()) {
    melodyPlayer.play();
  }

  if (!playerMoved && (js.isLeft() || js.isRight() || js.isUp())) {
    playerMoved = true;
    timeDisplay.unpause();
    lcd.clear();
  }

  if (!playerDied) {
    player.update();

    if (player.getY() == 0) {
      playerDied = true;
      timeDisplay.pause();
      dieTime = updateTime;

      lcd.clear();
      lcd.print("You lost a life!");
    }
  } else {
    if (updateTime - dieTime > deathDelay) {
      playerDied = false;
      timeDisplay.unpause();
      player.restoreToSafePosition();
    }
  }

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

  if (getCurrentDifficulty() != Difficulty::Hard &&
      player.getActualHeight() > 50) {
    setCurrentDifficulty(Difficulty::Medium);
  }
  if (player.getActualHeight() > 100) {
    setCurrentDifficulty(Difficulty::Hard);
  }

  if (levelMap.hasSpaceForNewPlatform()) {
    levelMap.generatePlatform();
  }
}

void PlayingState::render() const {
  if (paused) {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Game paused");
    lcd.setCursor(3, 1);
    lcd.print("Press JS");
    return;
  }

  if (playerMoved) {
    if (!playerDied) {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Height: ");
      lcd.print(player.getActualHeight());
      lcd.setCursor(15, 0);
      lcd.print(getCurrentDifficultyAsString()[0]);
    }

    lcd.setCursor(0, 1);
    lcd.write(heartCharCode);
    lcd.print(player.getLives());

    lcd.setCursor(4, 1);
    lcd.print("Score: ");
    lcd.print(score.getCurrentScore());
  }

  levelMap.render();
  timeDisplay.render();
}
