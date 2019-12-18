#pragma once

#include "Settings.h"

static const int giftPoints = 15;
static const int heightPoints = 5;

static const int easyPointMultiplier = 1;
static const int mediumPointMultiplier = 2;
static const int hardPointMultiplier = 3;

using ScoreT = unsigned;

class Score {
  ScoreT current = 0;

 public:
  ScoreT setCurrentScore(ScoreT newScore) { current = newScore; }
  ScoreT getCurrentScore() const { return current; }

  ScoreT getScoreMultiplier() {
    switch (settings.difficulty) {
      case Difficulty::Easy:
        return easyPointMultiplier;
      case Difficulty::Medium:
        return mediumPointMultiplier;
      case Difficulty::Hard:
        return hardPointMultiplier;
    }
  }

  void addPointsForGift() { current += giftPoints * getScoreMultiplier(); }

  void addPointsForHeight() { current += heightPoints * getScoreMultiplier(); }
};

extern Score score;
