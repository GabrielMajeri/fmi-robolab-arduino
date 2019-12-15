#pragma once

#include "Time.h"

enum class PlayerState : byte {
  Walking,
  Jumping,
  Falling,
};

class Player {
  byte x, y;
  byte accelY;
  PlayerState state;

  Time lastMoveTime;
  Time lastAirTime;

  void setPlayerCell(bool value);

  bool collidesLeft() const;
  bool collidesRight() const;
  bool collidesUp() const;
  bool collidesDown() const;

 public:
  Player();

  void update();

  byte getX() const;
  byte getY() const;

  int getRelativeX() const;
  int getRelativeY() const;

  void moveTo(byte x, byte y);
};

extern Player player;
