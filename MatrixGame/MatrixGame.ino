#include <LedControl.h>
#include <LiquidCrystal.h>
#include "Joystick.h"
#include "Map.h"
#include "Matrix.h"
#include "Melody.h"
#include "Player.h"

const byte pinV0 = 9;
const byte pinRS = 2;
const byte pinEnable = 3;
const byte pinD4 = 4;
const byte pinD5 = 5;
const byte pinD6 = 6;
const byte pinD7 = 7;
LiquidCrystal lcd(pinRS, pinEnable, pinD4, pinD5, pinD6, pinD7);

const byte pinDin = 13;
const byte pinClk = 12;
const byte pinLoad = 11;
const byte numDrivers = 2;
LedControl lc(pinDin, pinClk, pinLoad, numDrivers);

// Matrix matrix;
MelodyPlayer melody;
Map levelMap;
MapView currentView(levelMap, 0, 0);

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);

  // IDEA: use light sensor for auto brightness
  pinMode(pinV0, OUTPUT);   // PWN in loc de POTENTIOMETRU
  analogWrite(pinV0, 120);  // PWN in loc de POTENTIOMETRU

  // the zero refers to the MAX7219 number, it is zero for 1 chip
  for (int index = 0; index < lc.getDeviceCount(); ++index) {
    // Turn on display
    lc.shutdown(index, false);
    // Set brightness
    lc.setIntensity(index, 1);
    // Clear display
    lc.clearDisplay(index);
  }

  levelMap.createPlatform(0, 0, 10);
  levelMap.createPlatform(10, 1, 8);
  levelMap.createPlatform(18, 2, 8);
  levelMap.createPlatform(26, 3, 6);

  levelMap.createWall(0, 0, 20);

  levelMap.createPlatform(3, 2, 5);
  levelMap.createPlatform(1, 7, 3);
  levelMap.createPlatform(6, 5, 8);
  levelMap.createPlatform(2, 31, 28);

  melody.play();
}

void readInput() { js.read(); }

Time updateTime = 0;

void update() {
  updateTime = millis();

  melody.update();

  player.update();

  if (player.getRelativeX() > 4) {
    currentView.moveRight();
  }

  if (player.getRelativeX() < 3) {
    currentView.moveLeft();
  }

  if (player.getRelativeY() > 4) {
    currentView.moveUp();
  }

  if (player.getRelativeY() < 3) {
    currentView.moveDown();
  }
}

Time targetTime = 30000;

void render() {
  lcd.clear();

  lcd.print("P: ");
  lcd.print(player.getX());
  lcd.print(" ");
  lcd.print(player.getY());

  lcd.setCursor(0, 1);
  lcd.print("M: ");
  lcd.print(currentView.getX());
  lcd.print(" ");
  lcd.print(currentView.getY());

  for (byte row = 0; row < 8; ++row) {
    lc.setRow(0, row, currentView.get(row));
  }

  unsigned long currentTime = millis();
  unsigned long remainingTime = targetTime - currentTime;

  if (remainingTime < 1000) {
    targetTime = currentTime + 30000;
  }

  lc.setDigit(1, 0, (remainingTime / 10) % 10, false);
  lc.setDigit(1, 1, (remainingTime / 100) % 10, false);
  lc.setDigit(1, 2, (remainingTime / 1000) % 10, true);
  lc.setDigit(1, 3, (remainingTime / 10000) % 10, false);
}

void loop() {
  Time startTime = millis();

  readInput();
  update();
  render();

  Time currentTime = millis();
  Time elapsedTime = currentTime - startTime;
  if (elapsedTime < 15) {
    delay(15 - elapsedTime);
  }
}
