#pragma once

#include "BitOps.h"

static const byte matrixRows = 8, matrixColumns = 8;

class Map {
 public:
  using RowT = unsigned int;

  static const byte height = 32;
  static const byte width = 16;

  Map();

  RowT get(byte row) const;
  bool get(byte x, byte y) const;

  void set(byte x, byte y, bool value);

  void createPlatform(int x, int y, int length);
  void createWall(int x, int y, int length);

 private:
  Bitfield<RowT> data[height];
};

extern Map levelMap;

class MapView {
  Map& map;
  byte xOffset, yOffset;

 public:
  MapView(Map& map, byte x, byte y) : map(map), xOffset(x), yOffset(y) {}

  byte get(byte row) const {
    byte mapRow = yOffset + (matrixRows - 1 - row);
    byte mapColumn = map.width - (xOffset + matrixColumns);
    return (map.get(mapRow) >> mapColumn) & 0xFF;
  }

  byte getX() const;
  byte getY() const;

  void moveLeft();
  void moveRight();
  void moveUp();
  void moveDown();
};

extern MapView currentView;
