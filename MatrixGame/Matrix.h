#pragma once

class Matrix {
 public:
  static const byte rows = 8, columns = 8;

  void set(byte row, byte rowValue);

  void clear();
  void fill();
};

extern Matrix matrix;
