#include <string>
#include <algorithm>
#include <cctype>
#include <cpp_utils/string.hpp>

namespace cpp_utils {
namespace string {
string to_lower(const string &str)
{
    string result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](string::value_type c) {
        return std::tolower(c);
    });

    return result;
}

bool are_equal(const string &lhs, const string &rhs, CaseSensitivity case_sensitivity)
{
    string lhs_l;
    string rhs_l;
    if (case_sensitivity == CaseSensitivity::insensitive) {
        lhs_l = to_lower(lhs);
        rhs_l = to_lower(rhs);
    } else {
        lhs_l = lhs;
        rhs_l = rhs;
    }

    return lhs_l == rhs_l;
}

string replace_all(const string &where, const string &from, const string &to, CaseSensitivity case_sensitivity)
{
    if (where.empty())
        return string();

    string where_l;
    string from_l;
    if (case_sensitivity == CaseSensitivity::insensitive) {
        where_l = to_lower(where);
        from_l = to_lower(from);
    } else {
        where_l = where;
        from_l = from;
    }

    string result;
    for (string::size_type index = 0; index < where.size(); ++index) {
        if (where_l.find(from_l, index) == index) {// found match
            result += to;
            index += from.size() - 1;
        } else
            result += where[index];
    }
    return result;
}

string replace_begin(const string &where, const string &from, const string &to, CaseSensitivity case_sensitivity)
{
     if (where.empty())
        return string();

    string where_l;
    string from_l;
    if (case_sensitivity == CaseSensitivity::insensitive) {
        where_l = to_lower(where);
        from_l = to_lower(from);
    } else {
        where_l = where;
        from_l = from;
    }

    string result = where;
    string::size_type index = where_l.find(from_l);
    if (index != string::npos)
        result.replace(index, from.length(), to);
    return result;
}
}
}
