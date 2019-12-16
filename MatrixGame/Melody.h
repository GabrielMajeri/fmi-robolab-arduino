#pragma once

#include "Pitches.h"

// Melodies taken from
// https://www.hackster.io/joshi/piezo-christmas-songs-fd1ae9

// clang-format off
static const short notes[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};
// clang-format on

// clang-format off
static const byte noteDurations[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  /*
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
  */
};
// clang-format on

static const int noteCount = sizeof(noteDurations) / sizeof(noteDurations[0]);

class MelodyPlayer {
  static const byte pinBuzzer = 10;
  static const int baseDuration = 2000;
  bool playing = false;
  int currentNote = 0;
  int lastNoteTime = 0;

 public:
  void play() {
    playing = true;
    lastNoteTime = millis();
    tone(pinBuzzer, notes[currentNote],
         baseDuration / noteDurations[currentNote]);
  }

  void update() {
    if (!playing) {
      return;
    }

    int currentTime = millis();

    if (currentTime - lastNoteTime >
        baseDuration / noteDurations[currentNote]) {
      ++currentNote;
      tone(pinBuzzer, notes[currentNote],
           baseDuration / noteDurations[currentNote]);
      lastNoteTime = currentTime;
    }

    if (currentNote == noteCount) {
      playing = false;
      currentNote = 0;
      noTone(pinBuzzer);
    }
  }

  bool isPlaying() const { return playing; }
};
