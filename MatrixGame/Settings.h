#pragma once

enum class Difficulty : byte { Easy, Medium, Hard };

class Settings {
 public:
  char playerName[9] = "NoName";

  Difficulty difficulty = Difficulty::Easy;
};

extern Settings settings;
