#pragma once

#include "BitOps.h"
#include "Matrix.h"

class Map {
 public:
  using RowT = unsigned long;

  static const byte height = 32;
  static const byte width = 32;

  Map();

  RowT get(byte row) const { return data[row]; }

  void set(byte x, byte y, bool value) { data[y].set(width - x - 1, value); }

  void createPlatform(int x, int y, int length) {
    for (int i = 0; i < length; ++i) {
      set(x + i, y, true);
    }
  }

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
    byte mapRow = yOffset + (Matrix::rows - 1 - row);
    byte mapColumn = map.width - (xOffset + Matrix::columns);
    return (map.get(mapRow) >> mapColumn) & 0xFF;
  }

  byte getX() const { return xOffset; }

  byte getY() const { return yOffset; }

  void moveLeft() {
    if (xOffset > 0) {
      --xOffset;
    }
  }

  void moveRight() {
    if (xOffset < map.width - Matrix::columns) {
      ++xOffset;
    }
  }

  void moveUp() {
    if (yOffset < map.height - Matrix::rows) {
      ++yOffset;
    }
  }

  void moveDown() {
    if (yOffset > 0) {
      --yOffset;
    }
  }
};

extern MapView currentView;
