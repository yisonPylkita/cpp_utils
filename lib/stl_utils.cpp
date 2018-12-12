#include <cpp_utils/stl_utils.hpp>
#include <sstream>
#include <iomanip>

namespace vec {

namespace impl {
/// Serialize numeric type as hex
///
/// @param[in] number Number to serialize
/// @param[in] hex_len Length of string result
template<typename Numeric>
std::string number_to_hex(Numeric number, size_t hex_len = sizeof(Numeric) << 1)
{
    static const char *digits = "0123456789abcdef";
    std::string rc(hex_len, '0');
    for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
        rc[i] = digits[(number >> j) & 0x0f];
    return rc;
}
}

std::string to_string_hex(const std::vector<uint8_t> &container)
{
    if (container.empty())
        return "";
    std::string result;
    for (const auto elem : container)
        result += impl::number_to_hex(elem);
    return result;
}
}

std::string to_string_hex(unsigned char n)
{
    std::stringstream stream;
    stream << std::hex << std::setfill('0') << std::setw(2) << static_cast<unsigned>(n);
    return stream.str();
}