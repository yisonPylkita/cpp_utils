/// <summary>
/// Helpers for Windows errors handling
/// </summary>

#pragma once
#include <string>

namespace cpp_utils {
namespace win32 {
/// <summary>
/// Get last Windows error message
/// </summary>
/// <returns>Message for last set Windows error code</returns>
std::wstring GetLastErrorMessage();

/// <summary>
/// Converts given <paramref name="errorCode"/> to corresponding Windows error message
/// </summary>
/// <param name="errorCode">Windows error code to translate</param>
/// <returns>Error message to given <paramref name="errorCode"/></returns>
std::wstring ErrorCodeToString(DWORD errorCode);
}
}
