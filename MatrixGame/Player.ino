#include "Player.h"

#include "Map.h"

Player player;

void Player::setPlayerCell(bool state) { levelMap.set(x, y, state); }

Player::Player() : x(1), y(2) { setPlayerCell(true); }

byte Player::getX() const { return x; }
byte Player::getY() const { return y; }

int Player::getRelativeX() const { return int(x) - currentView.getX(); }
int Player::getRelativeY() const { return int(y) - currentView.getY(); }

void Player::moveTo(byte newX, byte newY) {
  setPlayerCell(false);
  x = newX;
  y = newY;
  setPlayerCell(true);
}

void Player::moveUp() {
  if (y < levelMap.height - 1) {
    moveTo(x, y + 1);
  }
}

void Player::moveDown() {
  if (y > 0) {
    moveTo(x, y - 1);
  }
}

void Player::moveLeft() {
  if (x > 0) {
    moveTo(x - 1, y);
  }
}

void Player::moveRight() {
  if (x < levelMap.width - 1) {
    moveTo(x + 1, y);
  }
}
