#include "Matrix.h"

const byte addr8x8Matrix = 0;

Matrix matrix;

void Matrix::set(byte row, byte rowValue) {
  lc.setRow(addr8x8Matrix, row, rowValue);
}

void Matrix::clear() { lc.clearDisplay(addr8x8Matrix); }

void Matrix::fill() {
  for (byte row = 0; row < 8; ++row) {
    set(row, 0xFF);
  }
}
