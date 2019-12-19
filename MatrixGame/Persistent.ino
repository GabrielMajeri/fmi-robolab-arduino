#include "Persistent.h"

#include <EEPROM.h>

PersistentData persistentData;

void resetPersistentData() {
  persistentData = {};
  savePersistentData();
}

void loadPersistentData() {
  byte* data = (byte*)&persistentData;
  for (byte i = 0; i < sizeof(persistentData); ++i) {
    data[i] = EEPROM.read(i);
  }
}

void savePersistentData() {
  const byte* data = (const byte*)&persistentData;
  for (byte i = 0; i < sizeof(persistentData); ++i) {
    EEPROM.write(i, data[i]);
  }
}
