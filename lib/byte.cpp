#include <cpp_utils/byte.hpp>
#include <cassert>
#include <limits>
#include <algorithm>

namespace bytes {
// TODO: this code was only tested on little endian machine
std::vector<uint8_t> to_bytes_le(uint32_t val, std::size_t num_bytes)
{
    assert(num_bytes > 0 && num_bytes <= 4 && "Conversion error - number of bytes should be in range [1 .. 4]");
    return std::vector<uint8_t>((std::uint8_t *)&val, (std::uint8_t *)&val + num_bytes);
}

std::vector<uint8_t> to_bytes_be(uint32_t val, std::size_t num_bytes)
{
    auto res = to_bytes_le(val, num_bytes);
    std::reverse(res.begin(), res.end());
    return res;
}
}