#pragma once

#include "Map.h"
#include "Melody.h"
#include "State.h"
#include "Time.h"

class StartingState : public State {
  Time lastScrollTime;

  void generateInitialMap();

 public:
  void onBegin() override;

  void update() override;

  void render() const override;
};
