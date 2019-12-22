#pragma once

using Time = unsigned long;

extern Time updateTime;

bool debounce(bool value, Time& lastTime, Time interval = 500);
bool debounce(Time& lastTime, Time interval = 200);
