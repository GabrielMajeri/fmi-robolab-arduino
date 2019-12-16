#pragma once

using Time = unsigned long;

extern Time updateTime;

bool debounce(bool value, Time& lastTime, Time delay = 500) {
  if (value && (updateTime - lastTime > delay)) {
    lastTime = updateTime;
    return true;
  }

  return false;
}
