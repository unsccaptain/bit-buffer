#pragma once

#include <iostream>

/// @brief:LSM->MSB
class BitWriter {
public:
  BitWriter(unsigned char *raw, unsigned max)
      : buffer(raw), max_buffer(max), pos(0), pos_bit(0) {
    raw[0] = 0;
  }

  /// @brief:write n byte to bit-stream
  void write_n_bit(uint64_t data, unsigned n);

  /// @brief:write 1 byte to bit-stream
  void write_8_bit(uint8_t data);

  /// @brief:write 1 word to bit-stream
  void write_16_bit(uint16_t data);

  /// @brief:write 2 word to bit-stream
  void write_32_bit(uint32_t data);

  /// @brief:write 1 quadword to bit-stream
  void write_64_bit(uint64_t data);

  /// @brief:get total size write
  unsigned size() { return pos + (pos_bit == 0 ? 0 : 1); }

private:
  uint8_t *StepToNextByte();

private:
  unsigned char *buffer; ///<< bit-stream
  unsigned max_buffer;   ///<< max size of buffer
  unsigned pos;          ///<< byte position where we write
  unsigned pos_bit;      ///<< bit position where we write
};