#pragma once

#include "Melody.h"
#include "Time.h"

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
  void setMelody(const Melody& melody);

  void play();
  void stop();
  void update();

  bool isPlaying() const;
};

extern MelodyPlayer melodyPlayer;
