#include "State.h"

#include "Persistent.h"

const Time frameTimeTarget = 30;

Time updateTime = 0;

void setup() {
  initHardware();
  getGameState().onBegin();

  // Uncomment to reset all highscores:
  // resetPersistentData();

  loadPersistentData();
}

void loop() {
  // Game loop based on this article:
  // https://gameprogrammingpatterns.com/game-loop.html

  Time startTime = millis();

  do {
    js.read();

    updateTime = millis();

    getGameState().update();
  } while (millis() - startTime < frameTimeTarget);

  getGameState().render();
}
