#pragma once

#include "Settings.h"

const byte maxHighScores = 3;

/// A high scored achieved by a player.
struct SavedScore {
  unsigned score;
  char name[playerNameLen];
};

/// This structure contains data which is persisted on the EEPROM.
struct PersistentData {
  Difficulty difficulty;
  SavedScore topPlayers[maxHighScores];
};

extern PersistentData persistentData;

/// Clears all data in the EEPROM back to empty values.
void resetPersistentData();

/// Load game data from the EEPROM.
void loadPersistentData();

/// Save game data to the EEPROM.
void savePersistentData();
