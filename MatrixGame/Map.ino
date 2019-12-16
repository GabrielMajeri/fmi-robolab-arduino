#include "Map.h"

#include "Hardware.h"

Map levelMap;
MapView currentView(levelMap, 0, 0);

Map::Map() : data() {}

Map::RowT Map::get(byte row) const { return data[row]; }
bool Map::get(byte x, byte y) const { return data[y].test(width - x - 1); }

void Map::set(byte x, byte y, bool value) { data[y].set(width - x - 1, value); }

void Map::createPlatform(int x, int y, int length) {
  Serial.print("Platform ");
  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.print(" ");
  Serial.println(length);

  for (int i = 0; i < length; ++i) {
    set(x + i, y, true);
  }
}

void Map::createWall(int x, int y, int length) {
  for (int i = 0; i < length; ++i) {
    set(x, y + i, true);
  }
}

void Map::render() const {
  for (byte row = 0; row < 8; ++row) {
    lc.setRow(0, row, currentView.get(row));
  }
}

byte MapView::getX() const { return xOffset; }

byte MapView::getY() const { return yOffset; }

void MapView::moveLeft() {
  if (xOffset > 0) {
    --xOffset;
  }
}

void MapView::moveRight() {
  if (xOffset < map.width - matrixColumns) {
    ++xOffset;
  }
}

void MapView::moveUp() {
  if (yOffset < map.height - matrixRows) {
    ++yOffset;
  }
}

void MapView::moveDown() {
  if (yOffset > 0) {
    --yOffset;
  }
}

void MapView::centerOnX() { xOffset = (map.width - matrixRows) / 2; }

void MapView::moveToTop() { yOffset = map.height - matrixRows; }
