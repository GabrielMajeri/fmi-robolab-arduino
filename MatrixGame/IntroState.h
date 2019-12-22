#pragma once

#include "State.h"

/// Intro screen displaying the game's name.
class IntroState : public State {
  Time startTime;

 public:
  void onBegin() override;

  void update() override;
};
