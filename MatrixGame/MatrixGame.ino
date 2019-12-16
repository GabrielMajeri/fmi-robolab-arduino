#include "State.h"

void setup() {
  initHardware();

  setGameState(GameState::Starting);
}

void readInput() { js.read(); }

Time updateTime = 0;

void update() {
  updateTime = millis();

  getGameState().update();
}

void render() {
  lcd.clear();

  getGameState().render();
}

void loop() {
  Time startTime = millis();

  readInput();
  update();
  render();

  Time currentTime = millis();
  Time elapsedTime = currentTime - startTime;
  if (elapsedTime < 15) {
    delay(15 - elapsedTime);
  }
}
