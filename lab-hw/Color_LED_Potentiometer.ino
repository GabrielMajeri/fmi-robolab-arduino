const int POT_RED_PIN = A0;
const int POT_GREEN_PIN = A1;
const int POT_BLUE_PIN = A2;

const int LED_RED_PIN = 6;
const int LED_GREEN_PIN = 5;
const int LED_BLUE_PIN = 3;

int lastTime = millis();
const int displayDelayMs = 500;

int redPotValue = 0,
  greenPotValue = 0,
  bluePotValue = 0;


void setup() {
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);

  Serial.begin(9600);
}


void printColor() {
  float red = redPotValue / 1024.0;
  float green = greenPotValue / 1024.0;
  float blue = bluePotValue / 1024.0;

  Serial.print("R: ");
  Serial.print(red);
  Serial.print(" G: ");
  Serial.print(green);
  Serial.print(" B: ");
  Serial.print(blue);
  Serial.println();
}


void updateColorChannel(int inPin, int outPin, int& potValue) {
  potValue = analogRead(inPin);
  int intensity = map(potValue, 0, 1023, 0, 255);
  analogWrite(outPin, intensity);
}


void updateRgbLed() {
  updateColorChannel(POT_RED_PIN, LED_RED_PIN, redPotValue);
  updateColorChannel(POT_GREEN_PIN, LED_GREEN_PIN, greenPotValue);
  updateColorChannel(POT_BLUE_PIN, LED_BLUE_PIN, bluePotValue);
}


void updateStats() {
  const int currentTime = millis();
  if (currentTime - lastTime > displayDelayMs) {
    printColor();
    lastTime = currentTime;
  }
}


void loop() {
  updateRgbLed();
  updateStats();
}
