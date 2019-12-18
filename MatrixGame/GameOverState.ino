#include "GameOverState.h"

#include "Matrix.h"

void GameOverState::render() const {
  matrix.fill();

  if (displayScore) {
    lcd.setCursor(1, 0);
    lcd.print("Final score:");
    lcd.setCursor(3, 1);
    lcd.print(score.getCurrentScore());
  } else {
    lcd.setCursor(1, 0);
    lcd.print("Press JS to");
    lcd.setCursor(0, 1);
    lcd.print("go back to menu.");
  }
}
