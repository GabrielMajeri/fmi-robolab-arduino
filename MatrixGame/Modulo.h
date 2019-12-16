#pragma once

template <byte M>
struct Modulo {
  byte value;

  Modulo(byte initial) : value(initial % M) {}

  operator byte() const { return value; }

  void operator++() { value = (value + 1) % M; }
  void operator--() { value = (value + M - 1) % M; }
};
