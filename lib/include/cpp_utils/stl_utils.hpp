#pragma once
#include <type_traits>
#include <string>
#include <vector>
#include <array>
#include <algorithm>


// TODO: wrap this in namespace
// namespace stl_utils {
namespace vec {
namespace operators {
template <typename T>
inline typename std::vector<T>  operator+(std::vector<T> &&lhs, T &&rhs)
{
    lhs.emplace_back(rhs);
    return lhs;
}

template <typename T>
inline typename std::vector<T>  operator+(const std::vector<T> &lhs, const T &rhs)
{
    std::vector<T> result(lhs);
    result.push_back(rhs);
    return result;
}

template <typename T>
inline typename std::vector<T>  operator+(std::vector<T> &&lhs, std::vector<T> &&rhs)
{
    std::vector<T> result;
    for (const auto &entry : lhs)
        result.push_back(entry);
    for (const auto &entry : rhs)
        result.push_back(entry);
    return result;
}

template <typename T>
inline typename std::vector<T>  operator+(const std::vector<T> &lhs, const std::vector<T> &rhs)
{
    std::vector<T> result;
    for (const auto &entry : lhs)
        result.push_back(entry);
    for (const auto &entry : rhs)
        result.push_back(entry);
    return result;
}

// TODO: WARNING: error prone - you may accidentally convert array to vector
// TODO: and while array.size() is the same as array.capacity you will find
// TODO: yourself with hard-to-find bug. Instead convert array to vector using vec::to_vector()
//template <typename T, std::size_t Size>
//typename std::vector<T>  operator+(const std::array<T, Size> &lhs, const std::vector<T> &rhs)
//{
//    if (lhs.empty())
//        return {};
//    return std::vector<T>{&lhs[0], &lhs[0] + lhs.size()} + rhs;
//}
//
//template <typename T, std::size_t Size>
//typename std::vector<T>  operator+(const std::vector<T> &lhs, const std::array<T, Size> &rhs)
//{
//    if (lhs.empty())
//        return {};
//    return lhs + std::vector<T>{&rhs[0], &rhs[0] + rhs.size()};
//}

template <typename T, std::size_t ArraySize>
inline typename std::vector<T>  operator+(std::vector<T> &&lhs, std::array<T, ArraySize> &&rhs)
{
    std::vector<T> result;
    for (const auto &entry : lhs)
        result.push_back(entry);
    for (const auto &entry : rhs)
        result.push_back(entry);
    return result;
}

template <typename T, std::size_t ArraySize>
inline typename std::vector<T>  operator+(std::vector<T> &lhs, const std::array<T, ArraySize> &rhs)
{
    std::vector<T> result;
    for (const auto &entry : lhs)
        result.push_back(entry);
    for (const auto &entry : rhs)
        result.push_back(entry);
    return result;
}

template <typename T>
inline typename std::vector<T>  operator+=(std::vector<T> &lhs, const T &rhs)
{
    lhs.push_back(rhs);
    return lhs;
}

template <typename T>
inline typename std::vector<T>  operator+=(std::vector<T> &lhs, const std::vector<T> &rhs)
{
    for (const auto &entry : rhs)
        lhs.push_back(entry);
    return lhs;
}

template <typename T, std::size_t Size>
inline typename std::vector<T>  operator+=(std::vector<T> &lhs, const std::array<T, Size> &rhs)
{
    for (const auto &entry : rhs)
        lhs.push_back(entry);
    return lhs;
}

template <typename T, std::size_t Size>
inline bool  operator==(const std::vector<T> &lhs, const std::array<T, Size> &rhs)
{
    if (lhs.size() != rhs.size())
        return false;
    for (typename std::vector<T>::size_type i = 0; i < lhs.size(); ++i)
        if (lhs[i] != rhs[i])
            return false;
    return true;
}

template <typename T, std::size_t Size>
inline bool  operator!=(const std::vector<T> &lhs, const std::array<T, Size> &rhs)
{
    return !(lhs == rhs);
}
}

template <typename T, size_t Size>
inline std::vector<T> to_vector(const std::array<T, Size> &lhs, size_t size)
{
    if (lhs.empty())
        return {};
    return {&lhs[0], &lhs[0] + size};
}

template <typename T>
inline std::vector<T> to_vector(T t)
{
    return std::vector<T>{t};
}

template <typename T>
inline void pop_front(std::vector<T> &lhs, typename std::vector<T>::size_type how_many)
{
    lhs = {lhs.begin() + how_many, lhs.end()};
}

template <typename T>
inline std::vector<T> subvec(const std::vector<T> &rhs, size_t start_index, size_t how_many)
{
    if (start_index >= rhs.size() || !how_many || start_index + how_many > rhs.size())
        return {};
    const auto sub_begin = rhs.begin() + start_index;
    return {sub_begin, sub_begin + how_many};
}

/// Split data to chunks with size of \p split_size
/// Last chunk can have size less than \p split size
template <typename T>
inline std::vector<std::vector<T>> split(const std::vector<T> &rhs, size_t split_size)
{
    if (rhs.empty())
        return {};
    if (rhs.size() < split_size)
        return {rhs};
    std::vector<std::vector<T>> out;
    for (size_t i = 0; i < rhs.size(); i += split_size) {
        auto end = rhs.begin() + i + split_size;
        if (end > rhs.end())
            end = rhs.end();
        out.emplace_back(std::vector<T>{rhs.begin() + i, end});
    }
    return out;
}

template <typename T>
inline std::vector<T> reverse(const std::vector<T> &rhs)
{
    auto res = rhs;
    std::reverse(res.begin(), res.end());
    return res;
}

template <typename T>
inline int find(const std::vector<T> &rhs, T elem, size_t start_pos = 0)
{
    const auto it = std::find(rhs.begin() + start_pos, rhs.end(), elem);
    if (it == rhs.end())
        return -1;
    return std::distance(rhs.begin(), it);
}

/// Checks if given container contains given element
///
/// @param[in]  container - where look for element
/// @param[in]  element - thing to look for
/// @returns    true if found, false otherwise
template <typename T>
inline bool contains(const std::vector<T> &container, const T &element)
{
    for (const auto &entry : container)
        if (entry == element)
            return true;
    return false;
}

/// Checks if given container contains element with given key
///
/// @param[in] container where look for element
/// @param[in] key key to search  for
/// @returns true if found, false otherwise
template <typename Key, typename Val>
bool contains_key(const std::vector<std::pair<Key, Val>> &container, const Key &key)
{
    for (const auto &entry : container)
        if (entry.first == key)
            return true;
    return false;
}

/// Remove first container element with the same key
///
/// @param[in] container where look for element
/// @param[in] key key to search  for
/// @returns true if found, false otherwise
template <typename Key, typename Val>
bool remove_key(std::vector<std::pair<Key, Val>> &container, const Key &key)
{
    for (auto it = container.begin(); it < container.end(); it++) {
        if (it->first == key) {
            container.erase(it);
            return true;
        }
    }
    return false;
}

///// Returns value of first element with key
/////
///// @param[in] container where look for element
///// @param[in] key key to search  for
///// @returns reference to T
//template <typename T>
//const T & get(const std::vector<std::pair<std::string, T>> &container, const std::string &key)
//{
//    for (const auto &entry : container)
//        if (entry.first == key)
//            return entry.second;
//}
//
///// Returns value of first element with key
/////
///// @param[in] container where look for element
///// @param[in] key key to search  for
///// @returns reference to T
//template <typename T>
//T & get(std::vector<std::pair<std::string, T>> &container, const std::string &key)
//{
//    for (const auto &entry : container)
//        if (entry.first == key)
//            return entry.second;
//}

/// Returns value of first element with key
///
/// @param[in] container where look for element
/// @param[in] key key to search  for
/// @returns pointer to T
/// @throws std::runtime_error on key not found
template <typename T>
inline const T & get(const std::vector<std::pair<std::string, T>> &container, const std::string &key)
{
    for (auto it = container.begin(); it!= container.end(); ++it)
        if (it->first == key)
            return it->second;
    throw std::runtime_error("Key '" + key + "' not found");
}

/// Checks if given container begins given element
///
/// @param[in]  container - where look for element
/// @param[in]  element - thing to look for
/// @returns    true if found, false otherwise
template <typename T>
inline bool begins_with(const std::vector<T> &container, const T &element)
{
    if (container.empty())
        return false;

    if (container[0] == element)
        return true;
    else
        return false;
}

/// Checks if given container begins given container of elements
///
/// @param[in]  container - where look for element
/// @param[in]  elements - thing to look for
/// @returns    true if found, false otherwise
template <typename T>
inline bool begins_with(const std::vector<T> &container, const std::vector<T> &elements)
{
    if (container.size() < elements.size())
        return false;

    for (typename std::vector<T>::size_type i = 0; i < elements.size(); ++i)
        if (container[i] != elements[i])
            return false;

    return true;
}

/// Checks if given container begins given container of elements
///
/// @param[in]  container - where look for element
/// @param[in]  elements - thing to look for
/// @returns    true if found, false otherwise
template <typename T, std::size_t Size>
inline bool begins_with(const std::vector<T> &container, const std::array<T, Size> &elements)
{
    if (container.size() < elements.size())
        return false;

    for (typename std::vector<T>::size_type i = 0; i < elements.size(); ++i)
        if (container[i] != elements[i])
            return false;

    return true;
}

/// Serialize std::vector<> of bytes
///
/// @param[in] container vector to serialize
std::string to_string_hex(const std::vector<uint8_t> &container);

/// Serialize std::array<> of bytes
///
/// @param[in] container array to serialize
/// @param[in] size how many bytes from array should be serialized
template <size_t Size>
inline std::string to_string_hex(const std::array<uint8_t, Size> &container, size_t size)
{
    if (container.empty())
        return "";
    if (size > Size)
        throw std::invalid_argument("Invalid number of bytes to stringify. Max number possible " + std::to_string(Size) + ", got " + std::to_string(size));
    return to_string_hex(std::vector<uint8_t>({&container[0], &container[0] + size}));
}

inline std::vector<uint8_t> from_string(const std::string &str)
{
    const auto str_cbegin = reinterpret_cast<const uint8_t *>(str.data());
    return std::vector<uint8_t>(str_cbegin, str_cbegin + str.size());
}

inline std::vector<uint8_t> hexstr_to_bytes(const std::string &hex_str)
{
    if (hex_str.empty() || hex_str.size() % 2)
        throw std::invalid_argument("Invalid size of hex string");

    std::vector<uint8_t> res{};
    res.reserve(hex_str.size() / 2);
    for (unsigned int i = 0; i < hex_str.length(); i += 2) {
        const auto a_byte = std::stoul(hex_str.substr(i, 2), nullptr, 16);
        res.push_back(static_cast<uint8_t>(a_byte));
    }
    return res;
}

inline std::vector<uint8_t> string_to_bytes(const std::string &str)
{
    const auto str_data = reinterpret_cast<const uint8_t *>(str.data());
    return std::vector<uint8_t>(str_data, str_data + str.size());
}

inline std::string bytes_to_string(const std::vector<uint8_t> &v)
{
    const auto v_data = reinterpret_cast<const char *>(v.data());
    return std::string(v_data, v_data + v.size());
}
}

std::string to_string_hex(unsigned char n);