#include <Windows.h>
#include <pro_utils/Exceptions.h>
#include <pro_utils/win32/Errors.hpp>

namespace pro_utils {
namespace win32 {
std::wstring GetLastErrorMessage()
{
    DWORD lastError = GetLastError();
    return ErrorCodeToString(lastError);
}

std::wstring ErrorCodeToString(DWORD errorCode)
{
    LPWSTR messageBuffer = nullptr;
    size_t size = FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorCode, 0,
        reinterpret_cast<LPWSTR>(&messageBuffer), 0, nullptr);
    if (!size)
        throw ProRuntimeException(L"Could not retrive message for Windows error code")
        .error(GetLastError());
    std::wstring errorMessage(messageBuffer, size);
    LocalFree(messageBuffer);
    while (!errorMessage.empty() && errorMessage.back() == L'\r' || errorMessage.back() == L'\n')
        errorMessage.pop_back();
    return errorMessage;
}
}
}
