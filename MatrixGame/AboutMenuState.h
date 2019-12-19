#pragma once

#include "State.h"
#include "Time.h"

class AboutMenuState : public State {
  Time lastScrollTime;
  byte topLineIndex;
  byte currentScroll, maxScroll;
  bool scrollingLeft;

  void addScrollDelayAtStart();
  void scrollToLine(byte index);

  byte printInfoLine(byte index, byte startingAt = 0) const;
  void printCurrentLines();

 public:
  void onBegin() override;

  void update() override;
  void render() const override;
};
