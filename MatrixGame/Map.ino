#include "Map.h"

#include "Hardware.h"
#include "Matrix.h"
#include "Score.h"
#include "Settings.h"
#include "TimeDisplay.h"

const Time giftBlinkDelay = 60;

Map levelMap;
MapView currentView(0, 0);

Map::Map() : data(), gifts() {}

Map::RowT Map::get(byte row) const { return data[row]; }
bool Map::get(byte x, byte y) const { return data[y].test(width - x - 1); }

bool Map::hasGiftAt(byte y) const { return gifts[y] != 0; }
byte Map::getGiftX(byte y) const { return gifts[y]; }

void Map::collectGift(byte y) {
  gifts[y] = 0;
  score.addPointsForGift();
  timeDisplay.increaseTimeLeftByDifficulty();
}

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

bool Map::hasSpaceForNewPlatform() const { return prevY < height - 5; }

void Map::generatePlatform() {
  byte x, y, length = 2 + random() % (long)getMaxPlatformLengthByDifficulty();

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

  // Add gifts randomly on some platforms
  if (random() % getGiftRarityByDifficulty() == 0) {
    gifts[y + 1] = x + length / 2;
  }

  createPlatform(x, y, length);

  prevX = x;
  prevY = y;
  prevLength = length;
}

void Map::shiftDown() {
  for (byte i = 0; i < height - 1; ++i) {
    data[i] = data[i + 1];
    gifts[i] = gifts[i + 1];
  }
  data[height - 1].value = 0;
  gifts[height - 1] = 0;
  --prevY;
}

void Map::render() const {
  for (byte row = 0; row < 8; ++row) {
    matrix.set(row, currentView.get(row));
  }
}

MapView::MapView(byte x, byte y) : xOffset(x), yOffset(y) {}

byte MapView::get(byte row) const {
  byte mapRow = yOffset + (matrix.rows - 1 - row);
  byte mapColumn = levelMap.width - (xOffset + matrix.columns);
  byte walls = (levelMap.get(mapRow) >> mapColumn) & 0xFF;

  if (levelMap.hasGiftAt(mapRow)) {
    byte giftX = levelMap.getGiftX(mapRow);
    if ((xOffset <= giftX) && (giftX < xOffset + matrix.columns)) {
      if (updateTime % giftBlinkDelay < giftBlinkDelay / 2) {
        walls |= (1 << (matrix.columns - 1 - (giftX - xOffset)));
      }
    }
  }

  return walls;
}

byte MapView::getX() const { return xOffset; }

byte MapView::getY() const { return yOffset; }

void MapView::moveLeft() {
  if (xOffset > 0) {
    --xOffset;
  }
}

void MapView::moveRight() {
  if (xOffset < levelMap.width - matrix.columns) {
    ++xOffset;
  }
}

void MapView::moveUp() {
  if (yOffset < levelMap.height - matrix.rows) {
    ++yOffset;
  }
}

void MapView::moveDown() {
  if (yOffset > 0) {
    --yOffset;
  }
}

void MapView::centerOnX() { xOffset = (levelMap.width - matrix.rows) / 2; }

void MapView::moveToTop() { yOffset = levelMap.height - matrix.rows; }
