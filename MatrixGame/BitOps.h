#pragma once

/// Wrapper for integral types, adding bit-manipulation operations.
template <typename I>
struct Bitfield {
  I value;

  operator I() const { return value; }

  /// Gets the value of a bit.
  bool test(byte position) const { return value & (I(1) << position); }

  /// Sets the value of a bit to the `value` parameter.
  void set(byte position, bool value) {
    if (value) {
      set(position);
    } else {
      clear(position);
    }
  }

  /// Sets the value of a bit to `true`.
  void set(byte position) { value |= (I(1) << position); }

  /// Resets the value of a bit to `false`.
  void clear(byte position) { value &= ~(I(1) << position); }
};
