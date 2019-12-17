#pragma once

#include "Pitches.h"
#include "Time.h"

struct Melody {
  const uint16_t* frequencies;
  const uint8_t* durations;
  const int noteCount;
};

extern Melody jingleBellsMelody;
extern Melody tetrisMelody;

class MelodyPlayer {
  const uint16_t* frequencies = nullptr;
  const uint8_t* durations = nullptr;
  int noteCount = 0;

  static const byte pinBuzzer = 10;
  static const Time baseDuration = 1800;
  bool playing = false;
  int currentNote = 0;
  Time nextNoteTime = 0;

 public:
  void setMelody(const Melody& melody) {
    frequencies = melody.frequencies;
    durations = melody.durations;
    noteCount = melody.noteCount;
  }

  void play() {
    if (noteCount == 0) {
      return;
    }

    playing = true;
    currentNote = 0;
    nextNoteTime = updateTime;
  }

  void update() {
    if (!playing) {
      return;
    }

    const uint16_t currentNoteFrequency =
        pgm_read_word_near(frequencies + currentNote);
    const Time currentNoteDuration =
        baseDuration / pgm_read_byte_near(durations + currentNote);

    if (updateTime > nextNoteTime) {
      if (currentNoteFrequency == 0) {
        noTone(pinBuzzer);
      } else {
        tone(pinBuzzer, currentNoteFrequency, currentNoteDuration);
      }

      nextNoteTime = updateTime + currentNoteDuration;
      ++currentNote;
    }

    if (currentNote == noteCount) {
      playing = false;
      noTone(pinBuzzer);
    }
  }

  bool isPlaying() const { return playing; }
};

extern MelodyPlayer melodyPlayer;
