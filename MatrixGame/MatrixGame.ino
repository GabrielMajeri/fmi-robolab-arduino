#include "State.h"

const Time frameTimeTarget = 30;

Time updateTime = 0;

void setup() { initHardware(); }

void readInput() { js.read(); }

void update() {
  updateTime = millis();

  getGameState().update();
}

void render() {
  lcd.clear();

  getGameState().render();
}

void loop() {
  // Game loop based on this article:
  // https://gameprogrammingpatterns.com/game-loop.html

  Time startTime = millis();

  while (millis() - startTime < frameTimeTarget) {
    readInput();
    update();
  }

  render();
}
