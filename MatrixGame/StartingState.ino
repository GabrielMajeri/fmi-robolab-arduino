#include "StartingState.h"

void StartingState::generateInitialMap() {
  randomSeed(2);

  byte x = 4, y = 0, length = 5;

  levelMap.createPlatform(x, y, length);

  while (levelMap.hasSpaceForNewPlatform()) {
    levelMap.generatePlatform();
  }
}
