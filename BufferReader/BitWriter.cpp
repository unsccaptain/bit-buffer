#include "BitWriter.h"

/// @brief:write n byte to bit-stream
void BitWriter::write_n_bit(uint64_t data, unsigned n) {
  while (n >= 8) {
    write_8_bit((uint8_t)(data & 0xff));
    data >>= 8;
    n -= 8;
  }

  uint8_t *value = buffer + pos;
  if (pos_bit + n < 8) {
    *value |= (uint8_t)((data & 0xff) << pos_bit);
    pos_bit = pos_bit + n;
  } else {
    /// write LSB
    *value |= (uint8_t)(data << pos_bit);
    value = StepToNextByte();
    pos_bit = n - (8 - pos_bit);
    if (pos_bit != 0)
      /// write MSB
      *value |= (uint8_t)(data >> (n - pos_bit));
  }
}

/// @brief:write 1 byte to bit-stream
void BitWriter::write_8_bit(uint8_t data) {
  uint8_t *value = buffer + pos;
  if (pos_bit != 0) {
    *value |= (uint8_t)(data << pos_bit);
    value = StepToNextByte();
    *value |= (uint8_t)(data >> (8 - pos_bit));
  } else {
    *value = data;
    StepToNextByte();
  }
}

/// @brief:write 1 word to bit-stream
void BitWriter::write_16_bit(uint16_t data) {
  write_8_bit(data & 0xff);
  write_8_bit(data >> 8);
}

/// @brief:write 2 word to bit-stream
void BitWriter::write_32_bit(uint32_t data) {
  write_16_bit(data & 0xffff);
  write_16_bit(data >> 16);
}

/// @brief:write 1 quadword to bit-stream
void BitWriter::write_64_bit(uint64_t data) {
  write_32_bit(data & 0xffff);
  write_32_bit(data >> 32);
}

uint8_t *BitWriter::StepToNextByte() {
  if (pos >= max_buffer - 1)
    throw(std::exception("BitWriter:buffer overflow"));
  buffer[++pos] = 0;
  return buffer + pos;
}