#include "Score.h"

#include "Persistent.h"
#include "Settings.h"
#include "Utility.h"

static const int giftPoints = 15;
static const int heightPoints = 5;
static const int extraLifePoints = 50;

Score score;

void Score::setCurrentScore(ScoreT newScore) { current = newScore; }

ScoreT Score::getCurrentScore() const { return current; }

void Score::reset() { current = 0; }

void Score::addPointsForGift() {
  current += giftPoints * getScoreMultiplierByDifficulty();
}

void Score::addPointsForHeight() {
  current += heightPoints * getScoreMultiplierByDifficulty();
}

void Score::addPointsForTimeLeft(byte secondsLeft) {
  current += secondsLeft * getScoreMultiplierByDifficulty();
}

void Score::addPointsForLivesLeft(byte extraLives) {
  current += extraLives * extraLifePoints * getScoreMultiplierByDifficulty();
}

bool Score::isHighScore() const {
  const SavedScore& lastPlayer = persistentData.topPlayers[maxHighScores - 1];
  return current >= lastPlayer.score;
}

void Score::updateHighScoreList() {
  SavedScore& lastPlayer = persistentData.topPlayers[maxHighScores - 1];

  strncpy(lastPlayer.name, playerName, playerNameLen);
  lastPlayer.score = current;

  for (int i = maxHighScores - 2; i >= 0; --i) {
    if (persistentData.topPlayers[i].score <
        persistentData.topPlayers[i + 1].score) {
      swap(persistentData.topPlayers[i], persistentData.topPlayers[i + 1]);
    }
  }
  savePersistentData();
}
