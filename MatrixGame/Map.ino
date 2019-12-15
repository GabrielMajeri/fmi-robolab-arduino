#include "Map.h"

Map::Map() : data() {}

Map::RowT Map::get(byte row) const { return data[row]; }
bool Map::get(byte x, byte y) const { return data[y].test(width - x - 1); }

void Map::set(byte x, byte y, bool value) { data[y].set(width - x - 1, value); }

void Map::createPlatform(int x, int y, int length) {
  for (int i = 0; i < length; ++i) {
    set(x + i, y, true);
  }
}

void Map::createWall(int x, int y, int length) {
  for (int i = 0; i < length; ++i) {
    set(x, y + i, true);
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
