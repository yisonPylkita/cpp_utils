#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>

typedef unsigned char byte_t; ///> Just a byte

constexpr uint8_t operator "" _u8(unsigned long long int val)
{
    return static_cast<uint8_t>(val);
}

constexpr uint16_t operator "" _u16(unsigned long long int val)
{
    return static_cast<uint16_t>(val);
}

namespace bytes {
std::vector<uint8_t> to_bytes_le(uint32_t val, std::size_t num_bytes = 4);
std::vector<uint8_t> to_bytes_be(uint32_t val, std::size_t num_bytes = 4);

inline uint16_t load_uint16_from_le(const uint8_t *raw_data)
{
    return ((uint16_t)(raw_data[1]) << 8) | (uint16_t)raw_data[0];
}

inline uint16_t load_uint16_from_be(const uint8_t *raw_data)
{
    return ((uint16_t) (raw_data[0]) << 8) | (uint16_t) raw_data[1];
}

inline uint32_t load_uint32_from_le(const uint8_t *raw_data)
{
    return (uint32_t)(raw_data[3]) << 24 | (uint32_t)raw_data[2] << 16 | (uint32_t)raw_data[1] << 8 | (uint32_t)raw_data[0];
}

inline uint32_t load_uint32_from_be(const uint8_t *raw_data)
{
    return ((uint32_t)(raw_data[0]) << 24) | (uint32_t)raw_data[1] << 16 | (uint32_t)raw_data[2] << 8 | (uint32_t)raw_data[3];
}
}