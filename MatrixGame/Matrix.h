#pragma once

#include "BitOps.h"

class Matrix {
  Bitfield<byte> matrix[8];

 public:
  static const byte rows = 8, columns = 8;

  Matrix();

  byte get(byte row) const { return matrix[row].value; }
  bool get(byte row, byte column) const { return matrix[row].test(column); }

  void set(byte row, byte column) { matrix[row].set(column); }
  void set(byte row, byte column, bool value) {
    if (value) {
      matrix[row].set(column);
    } else {
      matrix[row].clear(column);
    }
  }
};
