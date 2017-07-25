#pragma once
#include <Windows.h>

namespace pro_utils {
namespace bytes {
inline bool is_even(DWORD val)
{
    return !(val & 1);
}
}
}
