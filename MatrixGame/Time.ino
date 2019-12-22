#include "Time.h"

bool debounce(bool value, Time& lastTime, Time interval) {
  if (value && (updateTime > lastTime + interval)) {
    lastTime = updateTime;
    return true;
  }

  return false;
}

bool debounce(Time& lastTime, Time interval) {
  if (updateTime > lastTime + interval) {
    lastTime = updateTime;
    return true;
  }

  return false;
}
