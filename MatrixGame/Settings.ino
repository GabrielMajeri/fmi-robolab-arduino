#include "Settings.h"

#include "Persistent.h"
#include "Time.h"

Difficulty getCurrentDifficulty() { return persistentData.difficulty; }

void setCurrentDifficulty(Difficulty diff) { persistentData.difficulty = diff; }

const char* getCurrentDifficultyAsString() {
  switch (getCurrentDifficulty()) {
    case Difficulty::Easy:
      return "Easy";
    case Difficulty::Medium:
      return "Medium";
    case Difficulty::Hard:
      return "Hard";
  }
}

void increaseDifficulty() {
  byte difficulty = (byte)getCurrentDifficulty();
  difficulty = (difficulty + 1) % numDifficulties;
  persistentData.difficulty = (Difficulty)difficulty;
}

void decreaseDifficulty() {
  byte difficulty = (byte)getCurrentDifficulty();
  difficulty = (difficulty + numDifficulties - 1) % numDifficulties;
  persistentData.difficulty = (Difficulty)difficulty;
}

byte getMaxPlatformLengthByDifficulty() {
  switch (getCurrentDifficulty()) {
    case Difficulty::Easy:
      return 4;
    case Difficulty::Medium:
      return 3;
    case Difficulty::Hard:
      return 2;
  }
}

byte getGiftRarityByDifficulty() {
  switch (getCurrentDifficulty()) {
    case Difficulty::Easy:
      return 2;
    case Difficulty::Medium:
      return 4;
    case Difficulty::Hard:
      return 6;
  }
}

byte getStartingLivesByDifficulty() {
  switch (getCurrentDifficulty()) {
    case Difficulty::Easy:
      return 4;
    case Difficulty::Medium:
      return 3;
    case Difficulty::Hard:
      return 2;
  }
}

Time getStartingTimeByDifficulty() {
  switch (getCurrentDifficulty()) {
    case Difficulty::Easy:
      return 25000;
    case Difficulty::Medium:
      return 20000;
    case Difficulty::Hard:
      return 15000;
  }
}

Time getExtraTimeByDifficulty() {
  // On easier difficulties, each gift gives less extra time,
  // but they are more common.
  switch (getCurrentDifficulty()) {
    case Difficulty::Easy:
      return 1000;
    case Difficulty::Medium:
      return 1500;
    case Difficulty::Hard:
      return 2000;
  }
}

byte getScoreMultiplierByDifficulty() {
  // On harder difficulties, every score point is multiplied by a factor.
  switch (getCurrentDifficulty()) {
    case Difficulty::Easy:
      return 1;
    case Difficulty::Medium:
      return 2;
    case Difficulty::Hard:
      return 3;
  }
}
