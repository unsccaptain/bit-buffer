#pragma once

#include <iostream>

/// @note: only accepted pattern is that bits are stored from LSB(bit) to
/// MSB(bit)

/// @brief:LSM->MSB
class BitReader {
public:
  BitReader(unsigned char *raw, unsigned init_pos = 0)
      : buffer(raw), pos(init_pos), pos_bit(0) {}

  /// @brief: read arbitrary bits from bit-stream
  uint64_t read_n_bit(unsigned n);

  /// @brief:read 1 byte from bit-stream
  uint8_t read_8_bit();

  /// @brief:read 1 word from bit-stream
  uint16_t read_16_bit();

  /// @brief:read 2 word from bit-stream
  uint32_t read_32_bit();

  /// @brief:read 1 quadword from bit-stream
  uint64_t read_64_bit();

private:
  unsigned char *buffer; ///<< bit-stream
  unsigned pos;          ///<< byte position where we read
  unsigned pos_bit;      ///<< bit position where we read
};