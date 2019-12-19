#include "MelodyPlayer.h"

MelodyPlayer melodyPlayer;

void MelodyPlayer::setMelody(const Melody& melody) {
  frequencies = melody.frequencies;
  durations = melody.durations;
  noteCount = melody.noteCount;
}

void MelodyPlayer::play() {
  // Nothing to do if we don't have any melody active
  if (noteCount == 0) {
    return;
  }

  playing = true;
  currentNote = 0;
  nextNoteTime = updateTime;
}

void MelodyPlayer::update() {
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

bool MelodyPlayer::isPlaying() const { return playing; }
