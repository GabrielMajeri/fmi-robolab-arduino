#pragma once

#include "Time.h"

enum class PlayerState : byte {
  Walking,
  Jumping,
  Falling,
};

/// Class which controls all the player-related state, and the player's dot.
class Player {
  byte x, y;
  byte accelY;
  PlayerState state;
  unsigned long actualY, maxY;

  Time lastMoveTime;
  Time lastAirTime;

  byte lastSafeX, lastSafeY;
  byte lives;

  void setPlayerCell(bool value);

  bool collidesLeft() const;
  bool collidesRight() const;
  bool collidesUp() const;
  bool collidesDown() const;

 public:
  void reset();

  void update();

  byte getX() const;
  byte getY() const;

  unsigned long getActualHeight() const { return actualY; }

  int getRelativeX() const;
  int getRelativeY() const;

  void moveTo(byte x, byte y);

  void shiftDown();

  void setLives(byte newLives) { lives = newLives; }
  byte getLives() const { return lives; }
  bool hasNoLivesLeft() const { return lives == 0; }

  void restoreToSafePosition() { moveTo(lastSafeX, lastSafeY); }
};

extern Player player;
