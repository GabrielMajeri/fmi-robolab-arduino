const int KNOCK_SENSOR_PIN = A0;
const int KNOCK_THRESHOLD = 4;

const int MUSIC_DELAY = 5000;
const int OUTPUT_SPEAKER_PIN = 9;

const int STOP_BUTTON_PIN = 8;


unsigned long prevKnockTime = 0;
bool shouldPlayMusic = false;

int buttonState = 0;


void setup() {
  Serial.begin(9600);
  pinMode(KNOCK_SENSOR_PIN, INPUT);
  pinMode(OUTPUT_SPEAKER_PIN, OUTPUT);
  pinMode(STOP_BUTTON_PIN, INPUT_PULLUP);
}


// Detects input sounds from the piezospeaker and starts
// the countdown for the music.
void listenForKnock() {
  int soundIntensity = analogRead(KNOCK_SENSOR_PIN);

  if (soundIntensity >= KNOCK_THRESHOLD) {
    shouldPlayMusic = true;
    prevKnockTime = millis();
    Serial.println("Knock!");
  }
}


// Plays the music after a 5 second countdown.
void playMusic() {
  if (((millis() - prevKnockTime) > MUSIC_DELAY)) {
    int toneFreq = 0;

    // Create an alternating alarm tone
    if (millis() % 512 < 256) {
      toneFreq = 1600;
    } else {
      toneFreq = 440;
    }

    tone(OUTPUT_SPEAKER_PIN, toneFreq);
  }
}


// Checks the Stop Music button
void checkButton() {
  buttonState = digitalRead(STOP_BUTTON_PIN);
  if (buttonState == LOW) {
    shouldPlayMusic = false;
    noTone(OUTPUT_SPEAKER_PIN);
    Serial.println("Music stopped!");
  }
}


void loop() {
  if (!shouldPlayMusic) {
    listenForKnock();
  } else {
    playMusic();
    checkButton();
  }
}
