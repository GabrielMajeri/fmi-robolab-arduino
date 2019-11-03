/*
 * This simple program makes the builtin LED flash on and off.
 */

const int pinLed = LED_BUILTIN;

void setup() {
  pinMode(pinLed, OUTPUT);
}

void loop() {
  digitalWrite(pinLed, LOW);
  delay(1000);
  digitalWrite(pinLed, HIGH);
  delay(1000);
}
