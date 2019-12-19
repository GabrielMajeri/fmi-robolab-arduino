#include "Hardware.h"

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

Joystick js;

static byte heartCustomChar[] = {B00000, B00000, B01010, B11111,
                                 B11111, B01110, B00100, B00000};

void initHardware() {
  // Activate serial I/O
  Serial.begin(9600);

  // Configure the LCD
  lcd.begin(16, 2);

  // Add the custom character symbols
  lcd.createChar(heartCharCode, heartCustomChar);

  // Set the brightness of the LCD
  pinMode(pinV0, OUTPUT);
  analogWrite(pinV0, 120);

  // the zero refers to the MAX7219 number, it is zero for 1 chip
  for (int index = 0; index < lc.getDeviceCount(); ++index) {
    // Turn on display
    lc.shutdown(index, false);
    // Set brightness
    lc.setIntensity(index, 1);
    // Clear display
    lc.clearDisplay(index);
  }
}
