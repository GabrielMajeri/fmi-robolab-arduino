#pragma once

const byte playerNameLen = 6;
char playerName[playerNameLen + 1] = "NONAME";

enum class Difficulty : byte { Easy, Medium, Hard };
const byte numDifficulties = 3;

Difficulty getCurrentDifficulty();
void setCurrentDifficulty(Difficulty diff);

const char* getCurrentDifficultyAsString();

void increaseDifficulty();
void decreaseDifficulty();

byte getMaxPlatformLengthByDifficulty();
byte getGiftRarityByDifficulty();

byte getStartingLivesByDifficulty();
Time getStartingTimeByDifficulty();
Time getExtraTimeByDifficulty();

byte getScoreMultiplierByDifficulty();
