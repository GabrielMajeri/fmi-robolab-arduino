#pragma once

#include "BitOps.h"

/// Object storing the currently generated game map.
///
/// As part of the map gets shifted down, new platforms
/// can be generated at the top.
class Map {
 public:
  using RowT = unsigned int;

  static const byte height = 32;
  static const byte width = 16;

  Map();

  RowT get(byte row) const;
  bool get(byte x, byte y) const;

  bool hasGiftAt(byte y) const;
  byte getGiftX(byte y) const;
  void collectGift(byte y);

  void set(byte x, byte y, bool value);

  /// Add a new horizontal platform to the map.
  void createPlatform(int x, int y, int length);

  /// Add a new vertical wall to the map.
  void createWall(int x, int y, int length);

  bool hasSpaceForNewPlatform() const;

  void generatePlatform();

  /// Returns the Y coordinate of the previously generated platform.
  byte getPrevPlatformY() const { return prevY; }

  void shiftDown();

  void render() const;

 private:
  Bitfield<RowT> data[height];
  byte gifts[height];

  // Parameters of the previously generated platform
  byte prevX, prevY, prevLength;
};

extern Map levelMap;

/// View which remembers which part of the map is currently visible.
class MapView {
  byte xOffset, yOffset;

 public:
  MapView(byte x, byte y);

  byte get(byte row) const;

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
