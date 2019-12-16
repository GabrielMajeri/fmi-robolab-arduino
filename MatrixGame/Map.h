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

  /// Add a new horizontal platform to the map.
  void createPlatform(int x, int y, int length);

  /// Add a new vertical wall to the map.
  void createWall(int x, int y, int length);

  bool hasSpaceForNewPlatform() const { return prevY < height - 5; }

  void generatePlatform() {
    byte x, y, length = 3 + random() % 3;

    if (prevX >= width - prevLength - 1) {
      x = prevX - length - 1 - (random() % 2);
      y = prevY + 1 + random() % 2;
    } else if (prevX <= 3) {
      x = prevX + length + 1;
      y = prevY + 2;
    } else {
      if (random() % 2) {
        // To the left
        if (length > prevX) {
          length = prevX;
        }

        x = prevX - length + (random() % 2);
        y = prevY + 2 + random() % 2;
      } else {
        // To the right
        x = prevX + prevLength + random() % 2;
        y = prevY + 2 + random() % 2;

        if (x + length > width - 1) {
          x = width - length;
        }
      }
    }

    createPlatform(x, y, length);

    prevX = x;
    prevY = y;
    prevLength = length;
  }

  /// Returns the Y coordinate of the previously generated platform.
  byte getPrevPlatformY() const { return prevY; }

  void shiftDown() {
    for (byte i = 0; i < height - 1; ++i) {
      data[i] = data[i + 1];
    }
    data[height - 1].value = 0;
    --prevY;
  }

  void render() const;

 private:
  Bitfield<RowT> data[height];

  // Parameters of the previously generated platform
  byte prevX, prevY, prevLength;
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

  void centerOnX();
  void moveToTop();
};

extern MapView currentView;
