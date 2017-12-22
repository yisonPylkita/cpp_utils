#pragma once
#include <type_traits>
#include <string>
#include <vector>


namespace vec {

    template <typename T>
    typename std::vector<T>  pop_front(const std::vector<T> &lhs, typename std::vector<T>::size_type how_many)
    {
        return {lhs.begin() + how_many, lhs.end()};
    }

    template <typename T>
    std::vector<T> remove_all(const std::vector<T> &lhs, const T &val)
    {
        std::vector<T> result;
        for (auto &&item : lhs)
            if (item != val)
                result.push_back(item);

        return result;
    }

    namespace operators {

        template <typename T>
        typename std::vector<T>  operator+(const std::vector<T> &lhs, const std::vector<T> &rhs)
        {
            std::vector<T> result;
            for (const auto &entry : lhs)
                result.push_back(entry);
            for (const auto &entry : rhs)
                result.push_back(entry);
            return result;
        }

        template <typename T>
        typename std::vector<T>  operator+=(std::vector<T> &lhs, const T &rhs)
        {
            lhs.push_back(rhs);
            return lhs;
        }

        template <typename T>
        typename std::vector<T>  operator+=(std::vector<T> &lhs, const std::vector<T> &rhs)
        {
            for (const auto &entry : rhs)
                lhs.push_back(entry);
            return lhs;
        }

        template <typename T, std::size_t ArraySize>
        typename std::vector<T>  operator+=(std::vector<T> &lhs, const std::array<T, ArraySize> &rhs)
        {
            for (const auto &entry : rhs)
                lhs.push_back(entry);
            return lhs;
        }

//    template <typename T>
//    typename std::deque<T> operator+=(std::deque<T> &lhs, const std::vector<T> &rhs)
//    {
//        for (const auto &entry : rhs)
//            lhs.push_back(entry);
//        return lhs;
//    }

        template <typename T, std::size_t ArraySize>
        bool  operator==(const std::vector<T> &lhs, const std::array<T, ArraySize> &rhs)
        {
            if (lhs.size() != rhs.size())
                return false;
            for (typename std::vector<T>::size_type i = 0; i < lhs.size(); ++i)
                if (lhs[i] != rhs[i])
                    return false;
            return true;
        }

        template <typename T, std::size_t ArraySize>
        bool  operator!=(const std::vector<T> &lhs, const std::array<T, ArraySize> &rhs)
        {
            return !(lhs == rhs);
        }

    }

    /// Checks if given container contains given element
    ///
    /// @param[in]  container - where look for element
    /// @param[in]  element - thing to look for
    /// @returns    true if found, false otherwise
    template <typename T>
    bool contains(const std::vector<T> &container, const T &element)
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
    template <typename T>
    bool contains_key(const std::vector<std::pair<std::string, T>> &container, const std::string &key)
    {
        for (const auto &entry : container)
            if (entry.first == key)
                return true;
        return false;
    }

    /// Returns value of first element with key
    ///
    /// @param[in] container where look for element
    /// @param[in] key key to search  for
    /// @returns pointer to T or nullptr when not found
    template <typename T>
    const T * get(const std::vector<std::pair<std::string, T>> &container, const std::string &key)
    {
        for (const auto &entry : container)
            if (entry.first == key)
                return &entry.second;
        return nullptr;
    }

    /// Checks if given container begins given element
    ///
    /// @param[in]  container - where look for element
    /// @param[in]  element - thing to look for
    /// @returns    true if found, false otherwise
    template <typename T>
    bool begins_with(const std::vector<T> &container, const T &element)
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
    bool begins_with(const std::vector<T> &container, const std::vector<T> &elements)
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
    template <typename T, std::size_t ArraySize>
    bool begins_with(const std::vector<T> &container, const std::array<T, ArraySize> &elements)
    {
        if (container.size() < elements.size())
            return false;

        for (typename std::vector<T>::size_type i = 0; i < elements.size(); ++i)
            if (container[i] != elements[i])
                return false;

        return true;
    }

    /// Create symmetric difference out of two vectors
    template <typename T>
    std::pair<std::vector<T>, std::vector<T>> symmetric_difference(const std::vector<T> &v1, const std::vector<T> &v2)
    {

    };

    namespace impl {

        /// Serialize numeric type as hex
        ///
        /// @param[in] number Number to serialize
        /// @param[in] hex_len Length of string result
        template <typename Numeric>
        std::string number_to_hex(Numeric number, size_t hex_len = sizeof(Numeric) << 1)
        {
            static const char *digits = "0123456789ABCDEF";
            std::string rc(hex_len, '0');
            for (size_t i = 0, j = (hex_len - 1) * 4 ; i < hex_len; ++i, j -= 4)
                rc[i] = digits[(number >> j) & 0x0f];
            return rc;
        }
    }

    /// Serialize std::vector<> of fundamental types
    ///
    /// @param[in] container vector to serialize
    /// @param[in] mode serialize as "hex" or as "dec"
    /// @param[in] separator used to separate elements of \p container
    template <typename T>
    std::string to_string(const std::vector<T> &container, const std::string &mode = "hex", const std::string &separator = ", ")
    {
        static_assert(std::is_fundamental<T>::value, "Type needs to be a fundamental one");
        if (container.empty())
            return "";

        std::string result;
        for (const auto elem : container) {
            if (mode == "hex")
                result += impl::number_to_hex(elem);
            else
                result += std::to_string(elem);
            result += separator;
        }
        // last separator should be removed
        result.resize(result.size() - separator.size());

        return result;
    }
}
