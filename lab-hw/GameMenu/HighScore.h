#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include <EEPROM.h>

class HighScore {
  // Starting address in the EEPROM where to save the score
  static const int START_ADDRESS = 0;

  unsigned int score = 0;

public:
  HighScore() {
    loadScore();
  }

  void reset() {
    set(0);
  }

  void set(unsigned newScore) {
    score = newScore;
    saveScore();
  }

  unsigned get() {
    return score;
  }

  void loadScore() {
    score = 0;
    for (int i = 0; i < sizeof(score); ++i) {
      byte b = EEPROM.read(START_ADDRESS + i);
      score |= ((unsigned)b) << (i * 8);
    }
  }

  void saveScore() const {
    for (int i = 0; i < sizeof(score); ++i) {
      byte b = (score >> (i * 8)) & 0xFF;
      EEPROM.write(START_ADDRESS + i, b);
    }
  }
};

#endif
