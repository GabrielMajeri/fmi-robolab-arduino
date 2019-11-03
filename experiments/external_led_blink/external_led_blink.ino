/*
 * Makes an external LED blink.
 */
 
// Should be a PWM-supported pin.
const int LED_PIN = 3;

void setup() {
  pinMode(LED_PIN, OUTPUT);    
}

void loop() {
  for (int i = 1; i <= 6; ++i) {
    analogWrite(LED_PIN, i);
    delay(100);
  }
  delay(500);
  for (int i = 5; i >= 0; --i) {
    analogWrite(LED_PIN, i);
    delay(100);
  }
  delay(500);
}
