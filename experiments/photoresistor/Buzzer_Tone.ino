const int PHOTO_CELL_PIN = A0;const int BUZZER_PIN = 11;int photoCellValue = 0;int buzzerValue = 1000;void setup() {  pinMode(BUZZER_PIN, OUTPUT);  Serial.begin(9600);}void loop() {  photoCellValue = analogRead(PHOTO_CELL_PIN);    buzzerValue = map(photoCellValue, 200, 800, 200, 1500);    tone(BUZZER_PIN, buzzerValue, 1000);  delay(500);  noTone(BUZZER_PIN);  delay(800);}