#pragma once
#include <string>
#include <vector>

namespace pro_utils {
namespace string {
#ifdef UNICODE
    #define _T(x) L ## x
    typedef std::wstring string;
#else
    #define _T(x) x
    typedef std::string string;
#endif

/// <summary>
/// Should work in case-sensitive or case-insensitive mode ?
/// </summary>
enum class CaseSensitivity {
    sensitive,  //> Case sensitive mode
    insensitive //> Case insensitive mode
};

/// <summary>
/// Convert string to lower case
/// </summary>
/// <param name="str">String to convert</param>
/// <returns>Converted string</returns>
string to_lower(const string &str);

/// <summary>
/// Check if <paramref name="lhs"/> is equal to <paramref name="rhs"/>
/// </summary>
/// <param name="lhs">first item to compare</param>
/// <param name="rhs">second item to compare</param>
bool are_equal(const string &lhs, const string &rhs, CaseSensitivity case_sensitivity = CaseSensitivity::sensitive);

/// <summary>
/// Replace all occurencess of <paramref name="from"/> in <paramref name="where"/> to <paramref name="to"/>
/// </summary>
/// <param name="where">String to modify</param>
/// <param name="from">Replace from</param>
/// <param name="to">Replace to</param>
/// <returns>Modified string</returns>
string replace_all(const string &where, const string &from, const string &to, CaseSensitivity case_sensitivity = CaseSensitivity::sensitive);

/// <summary>
/// Replace first occurence of <paramref name="from"/> in <paramref name="where"/> 
/// to <paramref name="to"/> only if <paramref name="where"/> begins with <paramref name="from"/>
/// </summary>
/// <param name="where">String to modify</param>
/// <param name="from">Replace from</param>
/// <param name="to">Replace to</param>
/// <returns>Modified string</returns>
string replace_begin(const string &where, const string &from, const string &to, CaseSensitivity case_sensitivity = CaseSensitivity::sensitive);
}
}
