#include "Settings.h"

#include "Persistent.h"
#include "Time.h"

// On harder difficulties, every score point is multiplied by a factor.
const int easyPointMultiplier = 1;
const int mediumPointMultiplier = 2;
const int hardPointMultiplier = 3;

const Time startingTimeEasy = 25000;
const Time startingTimeMedium = 20000;
const Time startingTimeHard = 15000;

// On easier difficulties, each gift gives less extra time,
// but they are more common.
const Time extraTimeEasy = 1500;
const Time extraTimeMedium = 2500;
const Time extraTimeHard = 4000;

Difficulty getCurrentDifficulty() { return persistentData.difficulty; }

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
      return 3;
    case Difficulty::Hard:
      return 4;
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
      return startingTimeEasy;
    case Difficulty::Medium:
      return startingTimeMedium;
    case Difficulty::Hard:
      return startingTimeHard;
  }
}

Time getExtraTimeByDifficulty() {
  switch (getCurrentDifficulty()) {
    case Difficulty::Easy:
      return extraTimeEasy;
    case Difficulty::Medium:
      return extraTimeMedium;
    case Difficulty::Hard:
      return extraTimeHard;
  }
}

byte getScoreMultiplierByDifficulty() {
  switch (getCurrentDifficulty()) {
    case Difficulty::Easy:
      return easyPointMultiplier;
    case Difficulty::Medium:
      return mediumPointMultiplier;
    case Difficulty::Hard:
      return hardPointMultiplier;
  }
}
