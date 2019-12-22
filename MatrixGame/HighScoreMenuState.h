#pragma once

#include "Persistent.h"
#include "State.h"

/// Menu screen on which the top highest scores are listed.
class HighScoreMenuState : public State {
  byte topScoreIndex;

  /// Prints a score on the current LCD line.
  void printScore(byte index);

  /// Prints the currently visible scores on the LCD.
  void printScores();

 public:
  void onBegin() override;

  void update() override;
};
