#include "SettingsMenuState.h"

#include "Settings.h"

const byte settingsCount = 2;

const Time arrowBlinkDelay = 1000;
const Time caretBlinkDelay = 500;

const char nameFieldString[] = "Name: ";

void SettingsMenuState::clearSelectionArrow() {
  lcd.setCursor(0, currentIndex);
  lcd.print(" ");
}

void SettingsMenuState::printSelectionArrow() {
  lcd.setCursor(0, currentIndex);
  lcd.print(">");
}

void SettingsMenuState::printNameField() {
  lcd.print(nameFieldString);
  lcd.print(playerName);
}

void SettingsMenuState::printDifficultyLevelField() {
  lcd.print("Level: ");
  if (isEditingField && currentIndex == 1) {
    lcd.print("{");
  }

  lcd.print(getCurrentDifficultyAsString());

  if (isEditingField && currentIndex == 1) {
    lcd.print("}");
  }
}

void SettingsMenuState::printFields() {
  lcd.clear();

  lcd.setCursor(1, 0);
  printNameField();

  lcd.setCursor(0, 1);
  lcd.print(" ");
  printDifficultyLevelField();
}

void SettingsMenuState::changeToPrevChar() {
  char& ch = playerName[caretIndex];
  if (ch == 'A') {
    ch = ' ';
  } else if (ch == ' ') {
    ch = 'Z';
  } else {
    ch = 'A' + (ch - 'A' + 25) % 26;
  }
}

void SettingsMenuState::changeToNextChar() {
  char& ch = playerName[caretIndex];
  if (ch == 'Z') {
    ch = ' ';
  } else if (ch == ' ') {
    ch = 'A';
  } else {
    ch = 'A' + (ch - 'A' + 1) % 26;
  }
}

void SettingsMenuState::onBegin() {
  currentIndex = 0;
  isEditingField = false;

  printFields();
}

void SettingsMenuState::update() {
  if (js.isPressedDebounced()) {
    isEditingField = !isEditingField;

    if (currentIndex == 0) {
      caretIndex = 0;
    }

    printFields();
  }

  if (isEditingField) {
    if (updateTime % arrowBlinkDelay < 3 * arrowBlinkDelay / 4) {
      printSelectionArrow();
    } else {
      clearSelectionArrow();
    }

    if (currentIndex == 0) {
      if (js.isLeftDebounced()) {
        caretIndex = (caretIndex + playerNameLen - 1) % playerNameLen;
        printFields();
      }
      if (js.isRightDebounced()) {
        caretIndex = (caretIndex + 1) % playerNameLen;
        printFields();
      }

      if (js.isUpDebounced()) {
        changeToPrevChar();
      }
      if (js.isDownDebounced()) {
        changeToNextChar();
      }

      lcd.setCursor(sizeof(nameFieldString) + caretIndex, 0);
      if (updateTime % caretBlinkDelay > caretBlinkDelay / 2) {
        lcd.print('_');
      } else {
        lcd.print(playerName[caretIndex]);
      }
    } else if (currentIndex == 1) {
      if (js.isLeftDebounced()) {
        decreaseDifficulty();
        printFields();
      }
      if (js.isRightDebounced()) {
        increaseDifficulty();
        printFields();
      }
    }
  } else {
    printSelectionArrow();

    if (js.isDownDebounced()) {
      currentIndex = (currentIndex + 1) % settingsCount;
      printFields();
    }
    if (js.isUpDebounced()) {
      currentIndex = (currentIndex + settingsCount - 1) % settingsCount;
      printFields();
    }
    if (js.isLeftDebounced()) {
      setGameState(GameState::StartMenu);
    }
  }
}
