#include "Melody.h"

// Melody taken from
// https://www.hackster.io/joshi/piezo-christmas-songs-fd1ae9
const uint16_t PROGMEM jingleBellsFrequencies[] = {
    NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
    NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5, NOTE_E5,
};

const uint8_t PROGMEM jingleBellsDurations[] = {
    8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 2,
};

const int jingleBellsNoteCount =
    sizeof(jingleBellsDurations) / sizeof(jingleBellsDurations[0]);

Melody jingleBellsMelody{jingleBellsFrequencies, jingleBellsDurations,
                         jingleBellsNoteCount};

// Tetris theme taken from
// https://github.com/electricmango/Arduino-Music-Project
const uint16_t PROGMEM tetrisFrequencies[] = {
    NOTE_E5,  NOTE_E3, NOTE_B4,  NOTE_C5, NOTE_D5,  NOTE_E5, NOTE_D5,  NOTE_C5,
    NOTE_B4,  NOTE_A4, NOTE_A3,  NOTE_A4, NOTE_C5,  NOTE_E5, NOTE_A3,  NOTE_D5,
    NOTE_C5,  NOTE_B4, NOTE_E4,  NOTE_G4, NOTE_C5,  NOTE_D5, NOTE_E3,  NOTE_E5,
    NOTE_E3,  NOTE_C5, NOTE_A3,  NOTE_A4, NOTE_A3,  NOTE_A4, NOTE_A3,  NOTE_B2,
    NOTE_C3,  NOTE_D3, NOTE_D5,  NOTE_F5, NOTE_A5,  NOTE_C5, NOTE_C5,  NOTE_G5,
    NOTE_F5,  NOTE_E5, NOTE_C3,  0,       NOTE_C5,  NOTE_E5, NOTE_A4,  NOTE_G4,
    NOTE_D5,  NOTE_C5, NOTE_B4,  NOTE_E4, NOTE_B4,  NOTE_C5, NOTE_D5,  NOTE_G4,
    NOTE_E5,  NOTE_G4, NOTE_C5,  NOTE_E4, NOTE_A4,  NOTE_E3, NOTE_A4,  0,
    NOTE_E5,  NOTE_E3, NOTE_B4,  NOTE_C5, NOTE_D5,  NOTE_E5, NOTE_D5,  NOTE_C5,
    NOTE_B4,  NOTE_A4, NOTE_A3,  NOTE_A4, NOTE_C5,  NOTE_E5, NOTE_A3,  NOTE_D5,
    NOTE_C5,  NOTE_B4, NOTE_E4,  NOTE_G4, NOTE_C5,  NOTE_D5, NOTE_E3,  NOTE_E5,
    NOTE_E3,  NOTE_C5, NOTE_A3,  NOTE_A4, NOTE_A3,  NOTE_A4, NOTE_A3,  NOTE_B2,
    NOTE_C3,  NOTE_D3, NOTE_D5,  NOTE_F5, NOTE_A5,  NOTE_C5, NOTE_C5,  NOTE_G5,
    NOTE_F5,  NOTE_E5, NOTE_C3,  0,       NOTE_C5,  NOTE_E5, NOTE_A4,  NOTE_G4,
    NOTE_D5,  NOTE_C5, NOTE_B4,  NOTE_E4, NOTE_B4,  NOTE_C5, NOTE_D5,  NOTE_G4,
    NOTE_E5,  NOTE_G4, NOTE_C5,  NOTE_E4, NOTE_A4,  NOTE_E3, NOTE_A4,  0,
    NOTE_E4,  NOTE_E3, NOTE_A2,  NOTE_E3, NOTE_C4,  NOTE_E3, NOTE_A2,  NOTE_E3,
    NOTE_D4,  NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3,  NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_C4,  NOTE_E3, NOTE_A2,  NOTE_E3, NOTE_A3,  NOTE_E3, NOTE_A2,  NOTE_E3,
    NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3,  NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_E4,  NOTE_E3, NOTE_A2,  NOTE_E3, NOTE_C4,  NOTE_E3, NOTE_A2,  NOTE_E3,
    NOTE_D4,  NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3,  NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_C4,  NOTE_E3, NOTE_E4,  NOTE_E3, NOTE_A4,  NOTE_E3, NOTE_A2,  NOTE_E3,
    NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_E5,  NOTE_E3, NOTE_B4,  NOTE_C5, NOTE_D5,  NOTE_E5, NOTE_D5,  NOTE_C5,
    NOTE_B4,  NOTE_A4, NOTE_A3,  NOTE_A4, NOTE_C5,  NOTE_E5, NOTE_A3,  NOTE_D5,
    NOTE_C5,  NOTE_B4, NOTE_E4,  NOTE_G4, NOTE_C5,  NOTE_D5, NOTE_E3,  NOTE_E5,
    NOTE_E3,  NOTE_C5, NOTE_A3,  NOTE_A4, NOTE_A3,  NOTE_A4, NOTE_A3,  NOTE_B2,
    NOTE_C3,  NOTE_D3, NOTE_D5,  NOTE_F5, NOTE_A5,  NOTE_C5, NOTE_C5,  NOTE_G5,
    NOTE_F5,  NOTE_E5, NOTE_C3,  0,       NOTE_C5,  NOTE_E5, NOTE_A4,  NOTE_G4,
    NOTE_D5,  NOTE_C5, NOTE_B4,  NOTE_E4, NOTE_B4,  NOTE_C5, NOTE_D5,  NOTE_G4,
    NOTE_E5,  NOTE_G4, NOTE_C5,  NOTE_E4, NOTE_A4,  NOTE_E3, NOTE_A4,  0,
    NOTE_E5,  NOTE_E3, NOTE_B4,  NOTE_C5, NOTE_D5,  NOTE_E5, NOTE_D5,  NOTE_C5,
    NOTE_B4,  NOTE_A4, NOTE_A3,  NOTE_A4, NOTE_C5,  NOTE_E5, NOTE_A3,  NOTE_D5,
    NOTE_C5,  NOTE_B4, NOTE_E4,  NOTE_G4, NOTE_C5,  NOTE_D5, NOTE_E3,  NOTE_E5,
    NOTE_E3,  NOTE_C5, NOTE_A3,  NOTE_A4, NOTE_A3,  NOTE_A4, NOTE_A3,  NOTE_B2,
    NOTE_C3,  NOTE_D3, NOTE_D5,  NOTE_F5, NOTE_A5,  NOTE_C5, NOTE_C5,  NOTE_G5,
    NOTE_F5,  NOTE_E5, NOTE_C3,  0,       NOTE_C5,  NOTE_E5, NOTE_A4,  NOTE_G4,
    NOTE_D5,  NOTE_C5, NOTE_B4,  NOTE_E4, NOTE_B4,  NOTE_C5, NOTE_D5,  NOTE_G4,
    NOTE_E5,  NOTE_G4, NOTE_C5,  NOTE_E4, NOTE_A4,  NOTE_E3, NOTE_A4,  0,
    NOTE_E4,  NOTE_E3, NOTE_A2,  NOTE_E3, NOTE_C4,  NOTE_E3, NOTE_A2,  NOTE_E3,
    NOTE_D4,  NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3,  NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_C4,  NOTE_E3, NOTE_A2,  NOTE_E3, NOTE_A3,  NOTE_E3, NOTE_A2,  NOTE_E3,
    NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3,  NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_E4,  NOTE_E3, NOTE_A2,  NOTE_E3, NOTE_C4,  NOTE_E3, NOTE_A2,  NOTE_E3,
    NOTE_D4,  NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3,  NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_C4,  NOTE_E3, NOTE_E4,  NOTE_E3, NOTE_A4,  NOTE_E3, NOTE_A2,  NOTE_E3,
    NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3,
};

const uint8_t PROGMEM tetrisDurations[] = {
    8,  8, 8, 8, 8,  16, 16, 8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 4, 8, 8, 16, 16, 8,  8,  8,
    8,  8, 8, 8, 16, 16, 8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  4,
    4,  8, 8, 8, 8,  8,  16, 16, 8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 4, 8, 8,  16, 16, 8,  8,
    8,  8, 8, 8, 8,  16, 16, 8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    4,  4, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  16, 16, 8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 4,  8,  8,  16, 16,
    8,  8, 8, 8, 8,  8,  8,  16, 16, 8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 4, 4, 8,  8,  8,  8,  8,  16, 16, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  4,  8,  8,  16,
    16, 8, 8, 8, 8,  8,  8,  8,  16, 16, 8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 4, 4,  8,  8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 8, 8, 8,  8,  8,  8,  8,
    8,  8, 8, 8, 8,  8,
};

static const int tetrisNoteCount =
    sizeof(tetrisDurations) / sizeof(tetrisDurations[0]);

Melody tetrisMelody{tetrisFrequencies, tetrisDurations, tetrisNoteCount};
