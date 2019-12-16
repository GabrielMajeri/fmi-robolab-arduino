#include "Player.h"

#include "Joystick.h"
#include "Map.h"
#include "Time.h"

static const Time blinkDelay = 250;
static const Time moveDelay = 120;
static const Time airDelay = 100;

Player player;

void Player::setPlayerCell(bool value) { levelMap.set(x, y, value); }

bool Player::collidesLeft() const { return (x == 0) || levelMap.get(x - 1, y); }

bool Player::collidesRight() const {
  return (x == (levelMap.width - 1)) || levelMap.get(x + 1, y);
}

bool Player::collidesUp() const {
  return (y == (levelMap.height - 1)) || levelMap.get(x, y + 1);
}

bool Player::collidesDown() const { return (y == 0) || levelMap.get(x, y - 1); }

Player::Player()
    : x(6),
      y(2),
      accelY(0),
      state(PlayerState::Walking),
      lastMoveTime(0),
      lastAirTime(0) {
  setPlayerCell(true);
}

void Player::update() {
  if (updateTime - lastMoveTime > moveDelay) {
    if (js.isLeft() && !collidesLeft()) {
      moveTo(x - 1, y);
    } else if (js.isRight() && !collidesRight()) {
      moveTo(x + 1, y);
    }

    if (js.isUp() && state == PlayerState::Walking) {
      state = PlayerState::Jumping;
      accelY = 3;
    }

    lastMoveTime = updateTime;
  }

  if (state == PlayerState::Walking && !collidesDown()) {
    state = PlayerState::Falling;
  }

  if (updateTime - lastAirTime > airDelay) {
    switch (state) {
      case PlayerState::Jumping:
        if (accelY > 0) {
          if (!collidesUp()) {
            // Player is free to go up
            moveTo(x, y + 1);
          } else {
            // Player jumped and hit their head against a ceiling
            state = PlayerState::Falling;
            accelY = 0;
            break;
          }
          --accelY;
        } else {
          state = PlayerState::Falling;
        }
        break;
      case PlayerState::Falling:
        if (collidesDown()) {
          state = PlayerState::Walking;
        } else {
          moveTo(x, y - 1);
        }
        break;
      default:
        break;
    }

    lastAirTime = updateTime;
  }

  if (updateTime % blinkDelay > blinkDelay / 2) {
    setPlayerCell(true);
  } else {
    setPlayerCell(false);
  }
}

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

void Player::shiftDown() { --y; }
