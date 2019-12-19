#pragma once

#include "Persistent.h"
#include "State.h"

class HighScoreMenuState : public State {
  byte topScoreIndex;

  void printScore(byte index) {
    const SavedScore& score = persistentData.topPlayers[index];
    char name[8] = {};
    strncpy(name, score.name, playerNameLen);

    lcd.print(index + 1);
    lcd.print(". ");
    lcd.print(name);
    lcd.print(" ");
    lcd.print(score.score);
  }

  void printScores() {
    lcd.clear();
    printScore(topScoreIndex);

    if (topScoreIndex + 1 < maxHighScores) {
      lcd.setCursor(0, 1);
      printScore(topScoreIndex + 1);
    }
  }

 public:
  void onBegin() override { printScores(); }

  void update() override {
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
};
