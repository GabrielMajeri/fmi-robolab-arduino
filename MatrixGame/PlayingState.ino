#include "PlayingState.h"

#include "Score.h"

const Time deathDelay = 3000;

bool PlayingState::isGameOver() const {
  return player.hasNoLivesLeft() || timeDisplay.isFinished();
}

void PlayingState::onBegin() {
  melodyPlayer.setMelody(tetrisMelody);
  melodyPlayer.play();

  switch (settings.difficulty) {
    case Difficulty::Easy:
      player.setLives(5);
      break;
    case Difficulty::Medium:
      player.setLives(3);
      break;
    case Difficulty::Hard:
      player.setLives(2);
      break;
  }

  timeDisplay.pause();

  playerMoved = false;
  playerDied = false;
}

void PlayingState::update() {
  melodyPlayer.update();
  timeDisplay.update();

  if (!melodyPlayer.isPlaying()) {
    melodyPlayer.play();
  }

  if (!playerMoved && (js.isLeft() || js.isRight() || js.isUp())) {
    playerMoved = true;
    timeDisplay.unpause();
  }

  if (!playerDied) {
    player.update();

    if (player.getY() == 0) {
      playerDied = true;
      timeDisplay.pause();
      dieTime = updateTime;
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

  if (isGameOver()) {
    setGameState(GameState::GameOver);
  }

  if (levelMap.hasSpaceForNewPlatform()) {
    levelMap.generatePlatform();
  }
}

void PlayingState::render() const {
  if (!playerMoved) {
    lcd.setCursor(1, 0);
    lcd.print("Use JS to move.");
    lcd.setCursor(0, 1);
    lcd.print("Press for pause.");
  } else {
    if (!playerDied) {
      lcd.setCursor(1, 0);
      lcd.print("Height: ");
      lcd.print(player.getActualHeight());
    } else {
      lcd.setCursor(0, 0);
      lcd.print("You lost a life!");
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
