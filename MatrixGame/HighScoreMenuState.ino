#include "HighScoreMenuState.h"

void HighScoreMenuState::printScore(byte index) {
  const SavedScore& score = persistentData.topPlayers[index];

  // Copy to a temporary buffer to ensure string is null-terminated
  char name[8] = {};
  strncpy(name, score.name, playerNameLen);

  lcd.print(index + 1);
  lcd.print(". ");
  lcd.print(name);
  lcd.print(" ");
  lcd.print(score.score);
}

void HighScoreMenuState::printScores() {
  lcd.clear();

  lcd.setCursor(0, 0);
  printScore(topScoreIndex);

  if (topScoreIndex + 1 < maxHighScores) {
    lcd.setCursor(0, 1);
    printScore(topScoreIndex + 1);
  }
}

void HighScoreMenuState::onBegin() { printScores(); }

void HighScoreMenuState::update() {
  if (js.isDownDebounced()) {
    topScoreIndex = (topScoreIndex + 1) % maxHighScores;
    printScores();
  }
  if (js.isUpDebounced()) {
    topScoreIndex = (topScoreIndex + maxHighScores - 1) % maxHighScores;
    printScores();
  }
  if (js.isPressedDebounced()) {
    setGameState(GameState::StartMenu);
  }
}
