#include "GameOverState.h"

#include "Matrix.h"

const Time messageDisplayDelay = 5000;

void GameOverState::printScore() {
  printingScore = true;
  printingHighScore = false;

  lcd.clear();
  lcd.print("Congratulations!");
  lcd.setCursor(0, 1);
  lcd.print("Score: ");
  lcd.print(score.getCurrentScore());
}

void GameOverState::printHighScore() {
  printingScore = false;

  if (score.isHighScore()) {
    printingHighScore = true;
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("You've got a");
    lcd.setCursor(0, 1);
    lcd.print("new high score!");
  } else {
    printReturnToMenu();
  }
}

void GameOverState::printReturnToMenu() {
  printingHighScore = false;

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Press JS to");
  lcd.setCursor(0, 1);
  lcd.print("go back to menu.");
}

void GameOverState::onBegin() {
  lastTime = updateTime;

  matrix.fill();

  printScore();
}

void GameOverState::onEnd() {
  matrix.clear();
  score.reset();
}

void GameOverState::update() {
  if (debounce(printingScore, lastTime, messageDisplayDelay)) {
    printHighScore();
  }

  if (!printingScore &&
      debounce(printingHighScore, lastTime, messageDisplayDelay)) {
    printReturnToMenu();
  }

  if (js.isPressedDebounced()) {
    if (printingScore) {
      printHighScore();
    } else if (printingHighScore) {
      printReturnToMenu();
    } else {
      setGameState(GameState::StartMenu);
    }
  }
}
