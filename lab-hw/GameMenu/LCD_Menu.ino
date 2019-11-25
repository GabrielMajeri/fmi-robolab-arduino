#include "Joystick.h"
#include "Menu.h"
#include "HighScore.h"

Joystick js;
HighScore score;

const byte PIN_RS = 2;
const byte PIN_ENABLE = 3;

const byte PIN_D4 = 4;
const byte PIN_D5 = 5;
const byte PIN_D6 = 6;
const byte PIN_D7 = 7;

const byte PIN_CONTRAST = 10;

LiquidCrystal lcd(PIN_RS, PIN_ENABLE, PIN_D4, PIN_D5, PIN_D6, PIN_D7);

MainMenu mainMenu;
PlayMenu playMenu(score);
HighScoreMenu hsMenu(score);
SettingsMenu settingsMenu;

State currentState;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_CONTRAST, OUTPUT);
  analogWrite(PIN_CONTRAST, 120);

  lcd.begin(16, 2);
  lcd.clear();

  js.init();
}

void changeState(State newState) {
  currentState = newState;
  currentMenu().onBegin();
}

Menu& currentMenu() {
  switch (currentState) {
    case State::PLAY:
      return playMenu;
    case State::HIGH_SCORE:
      return hsMenu;
    case State::SETTINGS:
      return settingsMenu;
    default:
      return mainMenu;
  }
}

void loop() {
  js.read();
  //js.printDebugInfo();

  if (js.isPressed()) {
    currentMenu().onPress();
  }

  if (js.isMovedLeft()) {
    currentMenu().onLeft();
  } else if (js.isMovedRight()) {
    currentMenu().onRight();
  } else if (js.isMovedUp()) {
    currentMenu().onUp();
  } else if (js.isMovedDown()) {
    currentMenu().onDown();
  }

  currentMenu().onUpdate();
  currentMenu().display(lcd);

  delay(50);
}
