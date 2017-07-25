#pragma once
#include <vector>

namespace pro_utils {
template <typename T>
typename std::vector<T>  operator+(const std::vector<T> &lhs, const std::vector<T> &rhs)
{
    std::vector<T> result;
    for (const auto &entity : lhs)
        result.push_back(entity);
    for (const auto &entity : rhs)
        result.push_back(entity);
    return result;
}

///
/// @brief      Checks if given container contains given element
/// @param[in]  container - where look for element
/// @param[in]  element - thing to look for
/// @returns    true if found, false otherwise
///
template <typename T>
bool contains(const std::vector<T> &container, const T &element)
{
    for (const auto &entry : container)
        if (entry == element)
            return true;
    return false;
}
}
