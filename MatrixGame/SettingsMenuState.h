#pragma once

#include "Settings.h"
#include "State.h"

/// Menu where the player can change game settings,
/// such as player name or starting difficulty.
class SettingsMenuState : public State {
  byte currentIndex;
  byte caretIndex;
  bool isEditingField;

  void clearSelectionArrow();

  void printSelectionArrow();

  void printNameField();

  void printDifficultyLevelField();

  void printFields();

  void changeToPrevChar();
  void changeToNextChar();

 public:
  void onBegin() override;

  void update() override;
};
