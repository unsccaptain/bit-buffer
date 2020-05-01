#include "BitReader.h"

/// @brief: read arbitrary bits from bit-stream
uint64_t BitReader::read_n_bit(unsigned n) {
  uint64_t return_val = 0;
  unsigned shift_count = 0;
  while (n >= 8) {
    return_val = ((uint64_t)read_8_bit() << shift_count) + return_val;
    shift_count += 8;
    n -= 8;
  }

  /// from now on we will read a value which less than 1 byte
  uint64_t value = buffer[pos];
  if (pos_bit + n < 8) {
    /// pos after function return
    unsigned new_pos = pos_bit + n;

    /// z1 is a mask which filter the value of the current read and the next
    /// read
    uint64_t z1 = (~((((uint64_t)1) << pos_bit) - 1));
    /// z2 is a mask which filter the value of the next read
    uint64_t z2 = ((((uint64_t)1) << new_pos) - 1);

    /// so z1 & z2 will filter the value of the current read
    uint64_t mask = z1 & z2;
    value = (value & mask) >> pos_bit;
    pos_bit = new_pos;
  } else {
    /// "remain" will filter the value exist in the same byte of last read
    uint64_t remain = value & (0xff & (~((((uint64_t)1) << pos_bit) - 1)));
    uint64_t next_value = buffer[pos + 1];
    /// pos after function return
    unsigned next_bits = n - (8 - pos_bit);
    /// ((((uint64_t)1) << next_bits) - 1) will filter the value in next byte
    uint64_t next = next_value & ((((uint64_t)1) << next_bits) - 1);
    value = (remain >> pos_bit) + (next << (8 - pos_bit));
    pos_bit = next_bits;
    ++pos;
  }

  return_val += (value << shift_count);
  return return_val;
}

/// @brief:read 1 byte from bit-stream
uint8_t BitReader::read_8_bit() {
  uint8_t value = buffer[pos];
  if (pos_bit != 0) {
    /// mask1 will filter the value in the first byte
    unsigned mask1 = (0xff & (~((((uint64_t)1) << pos_bit) - 1)));
    unsigned mask1_value = (value & mask1) >> pos_bit;

    unsigned next_value = buffer[pos + 1];
    /// mask2 will filter the value in the next byte
    unsigned mask2 = ((((uint64_t)1) << pos_bit) - 1);
    unsigned mask2_value = (next_value & mask2) << (8 - pos_bit);

    /// we get actual value here
    value = mask1_value + mask2_value;
  }
  ++pos;
  return value;
}

/// @brief:read 1 word from bit-stream
uint16_t BitReader::read_16_bit() {
  uint16_t value = (uint64_t)read_8_bit();
  value += ((uint64_t)read_8_bit()) << 8;
  return value;
}

/// @brief:read 2 word from bit-stream
uint32_t BitReader::read_32_bit() {
  uint32_t value = (uint64_t)read_16_bit();
  value += ((uint64_t)read_16_bit()) << 16;
  return value;
}

/// @brief:read 1 quadword from bit-stream
uint64_t BitReader::read_64_bit() {
  uint64_t value = (uint64_t)read_32_bit();
  value += ((uint64_t)read_32_bit()) << 32;
  return value;
}