#include "AboutMenuState.h"

const char* const infoLines[] = {"Santa's Workshop",
                                 "Created by Gabriel Majeri",
                                 "Thanks to my teachers and colleagues",
                                 "Project for @UnibucRobotics",
                                 "GitHub: https://shorturl.at/cefm4",
                                 "Press JS to go to start menu",
                                 "Scroll down to go back up"};

const byte infoLinesNum = sizeof(infoLines) / sizeof(infoLines[0]);

const Time scrollDelay = 400;

void AboutMenuState::addScrollDelayAtStart() {
  lastScrollTime = updateTime + 2 * scrollDelay;
}

void AboutMenuState::scrollToLine(byte index) {
  topLineIndex = index;

  currentScroll = 0;
  maxScroll = 0;

  scrollingLeft = true;
  addScrollDelayAtStart();

  printCurrentLines();
}

byte AboutMenuState::printInfoLine(byte index, byte startingAt) const {
  const char* infoLine = infoLines[index];
  lcd.print(infoLine + startingAt);
  return strlen(infoLine);
}

void AboutMenuState::printCurrentLines() {
  lcd.clear();
  lcd.print(">");

  lcd.setCursor(1, 0);
  byte lineLen = printInfoLine(topLineIndex, currentScroll);
  maxScroll = lineLen / 2 + 1;

  if (topLineIndex + 1 < infoLinesNum) {
    lcd.setCursor(1, 1);
    printInfoLine(topLineIndex + 1);
  }
}

void AboutMenuState::onBegin() { scrollToLine(0); }

void AboutMenuState::update() {
  if (maxScroll > 0 && debounce(lastScrollTime, scrollDelay)) {
    if (scrollingLeft) {
      ++currentScroll;
      if (currentScroll == maxScroll) {
        scrollingLeft = false;
      }
    } else {
      --currentScroll;
      if (currentScroll == 0) {
        scrollingLeft = true;
        lastScrollTime = updateTime + 2 * scrollDelay;
      }
    }

    printCurrentLines();
  }

  if (js.isDownDebounced()) {
    scrollToLine((topLineIndex + 1) % infoLinesNum);
  }
  if (js.isUpDebounced()) {
    scrollToLine((topLineIndex + infoLinesNum - 1) % infoLinesNum);
  }

  if (js.isPressedDebounced()) {
    setGameState(GameState::StartMenu);
  }
}

void AboutMenuState::render() const {}
