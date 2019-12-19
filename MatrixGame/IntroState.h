#pragma once

#include "State.h"

class IntroState : public State {
  Time startTime;

 public:
  void onBegin() override;

  void update() override;
};
