#pragma once

#include "Pitches.h"

/// Structure containing all the information required to play back
/// a song using a `MelodyPlayer`.
struct Melody {
  const uint16_t* frequencies;
  const uint8_t* durations;
  const int noteCount;
};

/// Classic Christmas tune "Jinggle Bells"
extern Melody jingleBellsMelody;
/// Tetris theme music
extern Melody tetrisMelody;
