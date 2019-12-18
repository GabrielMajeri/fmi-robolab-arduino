#include "State.h"

#include "GameOverState.h"
#include "PlayingState.h"
#include "StartMenuState.h"
#include "StartingState.h"

class EmptyState : public State {
 public:
  void update() {}
  void render() const {
    lcd.setCursor(2, 0);
    lcd.print("Unreachable");
    lcd.setCursor(3, 1);
    lcd.print("game state");
  }
} emptyState;

StartMenuState startMenuState;
StartingState startingState;
PlayingState playingState;
GameOverState gameOverState;

State* currentState = &emptyState;

State& getGameState() { return *currentState; }

void setGameState(GameState newState) {
  currentState->onEnd();

  switch (newState) {
    case GameState::StartMenu:
      currentState = &startMenuState;
      break;

    case GameState::Starting:
      currentState = &startingState;
      break;

    case GameState::Playing:
      currentState = &playingState;
      break;

    case GameState::GameOver:
      currentState = &gameOverState;
      break;

    default:
      currentState = &emptyState;
      break;
  }

  currentState->onBegin();
}
