#pragma once

class Player {
  byte x, y;

  void setPlayerCell(bool state);

 public:
  Player();

  byte getX() const;
  byte getY() const;

  int getRelativeX() const;
  int getRelativeY() const;

  void moveTo(byte x, byte y);

  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
};

extern Player player;
