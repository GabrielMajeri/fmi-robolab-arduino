// Pin declarations
const byte PIN_A = 12;
const byte PIN_B = 8;
const byte PIN_C = 5;
const byte PIN_D = 3;
const byte PIN_E = 2;
const byte PIN_F = 11;
const byte PIN_G = 6;

const byte PIN_DP = 4;

const byte PIN_D1 = 7;
const byte PIN_D2 = 9;
const byte PIN_D3 = 10;
const byte PIN_D4 = 13;

const byte NUM_SEGMENTS = 7;
const byte NUM_DISPLAYS = 4;

const byte segmentPins[NUM_SEGMENTS] = {
  PIN_A, PIN_B, PIN_C, PIN_D, PIN_E, PIN_F, PIN_G,
};

const byte displayPins[NUM_DISPLAYS] = {
  PIN_D1, PIN_D2, PIN_D3, PIN_D4,
};

const byte NUM_DIGITS = 10;


const byte JS_PIN_SW = 1;
const byte JS_PIN_X = A0;
const byte JS_PIN_Y = A1;
const byte JS_THRESHOLD = 400;


const long BLINK_SPEED = 500;


const byte digits[NUM_DIGITS][NUM_SEGMENTS] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}, // 9
};

// State variables
int jsSwitch = 0;
int jsX = 0, jsY = 0;

byte digitStates[NUM_DISPLAYS] = { 0, 0, 0, 0 };
byte dpState = LOW;

byte activeDigit = 0;
bool lockedIn = false;
bool joystickPressed = false;
bool joystickMoved = false;

void selectDisplay(byte index) {
  for (int i = 0; i < NUM_DISPLAYS; ++i) {
    digitalWrite(displayPins[i], HIGH);
  }
  digitalWrite(displayPins[index], LOW);
}

void displayDigit(byte digit) {
  for (int i = 0; i < NUM_SEGMENTS; ++i) {
    digitalWrite(segmentPins[i], digits[digit][i]);
  }
}

void incrementMod(byte& value, byte modulo) {
  value = (value + 1) % modulo;
}

void decrementMod(byte& value, byte modulo) {
  value = (value - 1 + modulo) % modulo;
}


void updateJoystick() {
  jsSwitch = digitalRead(JS_PIN_SW);
  jsX = analogRead(JS_PIN_X);
  jsY = analogRead(JS_PIN_Y);

  if (jsSwitch == LOW) {
    if (!joystickPressed) {
      lockedIn = !lockedIn;
    }
    joystickPressed = true;
  } else {
    joystickPressed = false;
  }

  if (lockedIn) {
    if (jsX < 512 - JS_THRESHOLD) {
      if (!joystickMoved) {
        decrementMod(digitStates[activeDigit], NUM_DIGITS);
      }
      joystickMoved = true;
    } else if (jsX > 512 + JS_THRESHOLD) {
      if (!joystickMoved) {
        incrementMod(digitStates[activeDigit], NUM_DIGITS);
      }
      joystickMoved = true;
    } else {
      joystickMoved = false;
    }
  } else {
    if (jsY < 512 - JS_THRESHOLD) {
      if (!joystickMoved) {
        incrementMod(activeDigit, NUM_DISPLAYS);
      }
      joystickMoved = true;
    } else if (jsY > 512 + JS_THRESHOLD) {
      if (!joystickMoved) {
        decrementMod(activeDigit, NUM_DISPLAYS);
      }
      joystickMoved = true;
    } else {
      joystickMoved = false;
    }
  }
}

void updateDP() {
  if (lockedIn) {
    dpState = HIGH;
  } else {
    dpState = (millis() % BLINK_SPEED) > (BLINK_SPEED / 2);
  }
}

void updateDigitsDisplay() {
  for (int i = 0; i < NUM_DISPLAYS; ++i) {
    selectDisplay(i);
    displayDigit(digitStates[i]);
    digitalWrite(PIN_DP, i == activeDigit ? dpState : LOW);
    delay(5);
  }
}

void setup() {
  pinMode(JS_PIN_SW, INPUT_PULLUP);

  for (int i = 0; i < NUM_SEGMENTS; ++i) {
    pinMode(segmentPins[i], OUTPUT);
  }

  pinMode(PIN_DP, OUTPUT);

  for (int i = 0; i < NUM_DISPLAYS; ++i) {
    pinMode(displayPins[i], OUTPUT);
  }
}

void loop() {
  updateJoystick();
  updateDP();
  updateDigitsDisplay();
}
