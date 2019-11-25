#ifndef MENU_H
#define MENU_H

#include <LiquidCrystal.h>
#include "HighScore.h"

enum class State {
  MAIN_MENU,
  PLAY,
  HIGH_SCORE,
  SETTINGS,
};

const int NAME_LEN = 8;
char name[NAME_LEN + 1] = "EXAMPLE";
int startingLevelValue = 0;


int livesLeft = 3;


class Menu {
public:
  virtual void onBegin() {}
  virtual void onUpdate() {}

  virtual void onPress() {}

  virtual void onLeft() {}
  virtual void onRight() {}
  virtual void onUp() {}
  virtual void onDown() {}

  virtual void display(LiquidCrystal& lcd) = 0;
};

void changeState(State newState);
Menu& currentMenu();


class MainMenu : public Menu {
  int currentItem = 0;

public:
  void onPress() override {
    switch (currentItem) {
      case 0:
        changeState(State::PLAY);
        break;
      case 1:
        changeState(State::HIGH_SCORE);
        break;
      case 2:
        changeState(State::SETTINGS);
        break;
      default:
        break;
    }
  }

  void onLeft() override {
    currentItem -= 1;
    if (currentItem < 0) {
      currentItem = 2;
    }
  }

  void onRight() override {
    currentItem += 1;
    if (currentItem > 2) {
      currentItem = 0;
    }
  }

  void display(LiquidCrystal& lcd) override {
    lcd.clear();

    lcd.print(" ");
    lcd.print(currentItem == 0 ? ">" : " ");
    lcd.print("Play");

    lcd.print(" ");
    lcd.print(currentItem == 1 ? ">" : " ");
    lcd.print("HiScore");

    lcd.setCursor(0, 1);

    lcd.print("  ");
    lcd.print(currentItem == 2 ? ">" : " ");
    lcd.print("Settings");
  }
};

class PlayMenu : public Menu {
  int currentLevel;
  int currentScore;
  HighScore& highScore;

  long startTime;
  long lastLevelTime;

  bool gameOver = false;

public:
  PlayMenu(HighScore& score) : highScore(score) {
  }

  void onBegin() override {
    currentLevel = startingLevelValue;

    startTime = millis();
    lastLevelTime = startTime;
  }

  void onUpdate() override {
    long currentTime = millis();

    if (!gameOver && (currentTime - lastLevelTime) / 1000 > 5) {
      currentLevel += 1;
      lastLevelTime = currentTime;
    }

    if ((currentTime - startTime) / 1000 > 10) {
      gameOver = true;
    }

    currentScore = currentLevel * 3;
  }

  void onPress() {
    if (gameOver) {
      if (currentScore > highScore.get()) {
        highScore.set(currentScore);
      }

      changeState(State::MAIN_MENU);
    }
  }

  void display(LiquidCrystal& lcd) override {
    lcd.clear();

    if (!gameOver) {
      lcd.print("Lives: ");
      lcd.print(livesLeft);
      lcd.print(" ");
      lcd.print("Lvl: ");
      lcd.print(currentLevel);

      lcd.setCursor(0, 1);
      lcd.print("   Score: ");
      lcd.print(currentScore);
    } else {
      lcd.print("Congratulations!");

      lcd.setCursor(0, 1);
      lcd.print("Press JS to exit");
    }
  }
};

class HighScoreMenu : public Menu {
  HighScore& hiScore;

public:
  HighScoreMenu(HighScore& score) : hiScore(score) {
  }

  void onPress() override {
    changeState(State::MAIN_MENU);
  }

  void onRight() override {
    hiScore.reset();
  }

  void display(LiquidCrystal& lcd) override {
    lcd.clear();
    lcd.print("High score:");
    lcd.print(hiScore.get());
    lcd.setCursor(0, 1);
    lcd.print("Press JS to exit");
  }
};

class SettingsMenu : public Menu {
  static const int BLINK_DELAY = 500;

  int currentLine = 0;
  bool editingActive = false;
  bool editingName = false;
  bool editingLevel = false;

  int caretPosition = 0;

public:
  void onPress() {
    editingActive = !editingActive;
    if (currentLine == 0) {
      editingName = !editingName;
    } else {
      editingLevel = !editingLevel;
    }
  }

  void onLeft() {
    if (!editingActive) {
      changeState(State::MAIN_MENU);
    }
    if (editingName) {
      caretPosition -= 1;
      if (caretPosition < 0) {
        caretPosition = NAME_LEN - 1;
      }
    }
  }

  void onRight() {
    if (editingName) {
      caretPosition += 1;
      if (caretPosition >= NAME_LEN) {
        caretPosition = 0;
      }
    }
  }

  void onUp() {
    if (!editingActive) {
      currentLine -= 1;
      if (currentLine < 0) {
        currentLine = 1;
      }
    } else {
      if (editingName) {
        if (name[caretPosition] == ' ') {
          name[caretPosition] = 'A';
        } else {
          name[caretPosition] = name[caretPosition] + 1;
        }
        if (name[caretPosition] > 'Z') {
          name[caretPosition] = ' ';
        }
      }
      if (editingLevel) {
        startingLevelValue += 1;
        if (startingLevelValue > 9) {
          startingLevelValue = 0;
        }
      }
    }
  }

  void onDown() {
    if (!editingActive) {
      currentLine += 1;
      if (currentLine > 1) {
        currentLine = 0;
      }
    } else {
      if (editingName) {
        if (name[caretPosition] == ' ') {
          name[caretPosition] = 'Z';
        } else {
          name[caretPosition] = name[caretPosition] - 1;
        }
        if (name[caretPosition] < 'A') {
          name[caretPosition] = ' ';
        }
      }
      if (editingLevel) {
        startingLevelValue -= 1;
        if (startingLevelValue < 0) {
          startingLevelValue = 9;
        }
      }
    }
  }

  void display(LiquidCrystal& lcd) override {
    lcd.clear();
    lcd.print(" Name: ");
    lcd.print(name);

    lcd.setCursor(0, 1);
    lcd.print(" Start Level: ");
    lcd.print(startingLevelValue);

    lcd.setCursor(0, currentLine);
    if (!editingActive) {
      lcd.print(">");
    } else {
      if ((millis() % (2 * BLINK_DELAY)) < BLINK_DELAY) {
        lcd.print(">");
      } else {
        lcd.print(" ");
      }
    }

    if (editingName) {
      if ((millis() % (2 * BLINK_DELAY)) > BLINK_DELAY) {
        lcd.setCursor(7 + caretPosition, currentLine);
        lcd.print("_");
      }
    }
  }
};

#endif
