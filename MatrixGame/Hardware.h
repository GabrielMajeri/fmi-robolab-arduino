#pragma once

#include <LedControl.h>
#include <LiquidCrystal.h>
#include "Joystick.h"

extern LiquidCrystal lcd;
extern LedControl lc;
extern Joystick js;

const byte heartCharCode = 0;

/// Initializes the hardware components for the rest of the game to use.
void initHardware();
