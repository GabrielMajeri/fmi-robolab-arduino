#include <LedControl.h>
#include <LiquidCrystal.h>
#include "Joystick.h"

const byte pinV0 = 9;
const byte pinRS = 2;
const byte pinEnable = 3;
const byte pinD4 = 4;
const byte pinD5 = 5;
const byte pinD6 = 6;
const byte pinD7 = 7;
LiquidCrystal lcd(pinRS, pinEnable, pinD4, pinD5, pinD6, pinD7);

const byte pinDin = 12;
const byte pinClk = 11;
const byte pinLoad = 10;
const byte numDrivers = 1;
LedControl lc(pinDin, pinClk, pinLoad, numDrivers);

Joystick js;

unsigned long lastUpdateTime = 0;
const int updateTimestep = 150;

template <typename I>
bool testBit(I value, byte position) {
  return value & (1 << position);
}

template <typename I>
I clearBit(I value, byte position) {
  return value & ~(1 << position);
}

template <typename I>
I setBit(I value, byte position) {
  return value | (1 << position);
}

class Matrix {
  // clang-format off
  byte matrix[8] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01000010,
    0b00111100,
    0b00000000,
    0b00000000,
  };
  // clang-format on

 public:
  byte get(byte row) { return matrix[row]; }
  bool get(byte row, byte column) { return testBit(matrix[row], column); }
  void set(byte row, byte column) { matrix[row] = setBit(matrix[row], column); }
  void set(byte row, byte column, bool value) {
    matrix[row] =
        value ? setBit(matrix[row], column) : clearBit(matrix[row], column);
  }
};

Matrix matrix;

void setup() {
  lcd.begin(16, 2);

  // IDEA: use light sensor for auto brightness
  pinMode(pinV0, OUTPUT);   // PWN in loc de POTENTIOMETRU
  analogWrite(pinV0, 120);  // PWN in loc de POTENTIOMETRU

  // the zero refers to the MAX7219 number, it is zero for 1 chip
  for (int index = 0; index < lc.getDeviceCount(); ++index) {
    lc.shutdown(index, false);  // turn off power saving, enables display
    lc.setIntensity(index, 1);  // sets brightness (0~15 possible values)
    lc.clearDisplay(index);     // clear screen
  }
}

void readInput() { js.read(); }

class Player {
  byte row, column;

  void setPlayerCell(bool state) { matrix.set(row, column, state); }

 public:
  Player() : row(1), column(2) { setPlayerCell(true); }

  int getRow() const { return row; }

  int getColumn() const { return column; }

  void moveUp() {
    setPlayerCell(false);
    row = (row + 8 - 1) % 8;
    setPlayerCell(true);
  }

  void moveDown() {
    setPlayerCell(false);
    row = (row + 1) % 8;
    setPlayerCell(true);
  }

  void moveLeft() {
    setPlayerCell(false);
    column = (column + 8 - 1) % 8;
    setPlayerCell(true);
  }

  void moveRight() {
    setPlayerCell(false);
    column = (column + 1) % 8;
    setPlayerCell(true);
  }
};

Player player;

void update() {
  if (js.isMoveUp()) {
    player.moveUp();
    lastUpdateTime = millis();
  }

  if (js.isMoveDown() &&
      matrix.get(player.getRow() + 1, player.getColumn()) == false) {
    player.moveDown();
    lastUpdateTime = millis();
  }

  if (js.isMoveLeft() &&
      (player.getColumn() == 0 ||
       matrix.get(player.getRow(), player.getColumn() - 1) == false)) {
    player.moveLeft();
    lastUpdateTime = millis();
  }

  if (js.isMoveRight() &&
      (player.getColumn() == 7 ||
       matrix.get(player.getRow(), player.getColumn() + 1)) == false) {
    player.moveRight();
    lastUpdateTime = millis();
  }

  if (millis() - lastUpdateTime > updateTimestep) {
    lastUpdateTime = millis();

    if (player.getColumn() == 7 ||
        matrix.get(player.getRow() + 1, player.getColumn()) != true) {
      player.moveDown();
    }
  }
}

void render() {
  lcd.clear();
  lcd.print("hello ");
  lcd.print(player.getRow());
  lcd.print(" ");
  lcd.print(player.getColumn());
  lcd.setCursor(0, 1);
  lcd.print("X:");
  lcd.print(js.getX());
  lcd.print(" | Y:");
  lcd.print(js.getY());

  for (byte row = 0; row < 8; ++row) {
    lc.setRow(0, row, matrix.get(row));
  }
}

void loop() {
  readInput();
  update();
  render();
  delay(5);
}
