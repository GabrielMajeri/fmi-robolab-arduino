#include "State.h"

#include "AboutMenuState.h"
#include "GameOverState.h"
#include "HighScoreMenuState.h"
#include "IntroState.h"
#include "PlayingState.h"
#include "SettingsMenuState.h"
#include "StartMenuState.h"
#include "StartingState.h"

IntroState introState;
StartMenuState startMenuState;
HighScoreMenuState highScoreMenuState;
AboutMenuState aboutMenuState;
SettingsMenuState settingsMenuState;
StartingState startingState;
PlayingState playingState;
GameOverState gameOverState;

State* currentState = &introState;

State& getGameState() { return *currentState; }

void setGameState(GameState newState) {
  // Give the state a final render
  currentState->render();

  // Cleanup after finishing this state
  currentState->onEnd();

  switch (newState) {
    case GameState::Intro:
      currentState = &introState;
      break;

    case GameState::HighScoreMenu:
      currentState = &highScoreMenuState;
      break;

    case GameState::AboutMenu:
      currentState = &aboutMenuState;
      break;

    case GameState::SettingsMenu:
      currentState = &settingsMenuState;
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
      currentState = &startMenuState;
      break;
  }

  currentState->onBegin();
}
