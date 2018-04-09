#include <string>
#include <vector>
#include "Catch.hpp"
#include <cpp_utils/preprocessor.hpp>

TEST_CASE("There can be multiple unique variables in one scope", "[preprocessor]")
{
    int UNIQUE = 0;
    std::wstring UNIQUE = L"asdasd";
    std::vector<std::wstring> UNIQUE =
    {
        L"asda",
        L"a1231as",
        L"8as7dasgd"
    };
    double UNIQUE = 999999.;
}

// They can also have global or translation unit scope
namespace {
const int UNIQUE = 0;
std::vector<std::wstring> UNIQUE =
{
    L"asda",
    L"a1231as",
    L"8as7dasgd"
};
}
std::wstring UNIQUE = L"asdasd";
double UNIQUE = 999999.;

TEST_CASE("Unique variables can be created in diffrent scopes", "[preprocessor]")
{
    int UNIQUE = 0;
    {
        int UNIQUE = 0;
        std::wstring UNIQUE = L"asdasd";
        std::vector<std::wstring> UNIQUE =
        {
            L"asda",
            L"a1231as",
            L"8as7dasgd"
        };
        double UNIQUE = 999999.;
    }
    double UNIQUE = 999999.;
}

TEST_CASE("Variable name is unique", "[preprocessor]")
{
    int UNIQUE = 0;
    int UNIQUE = 1;
    int UNIQUE = 2;
    int UNIQUE = 3;
    int UNIQUE = 4;
    int UNIQUE = 5;
    int UNIQUE = 6;
    int UNIQUE = 7;
    int UNIQUE = 8;
    int UNIQUE = 9;
    int UNIQUE = 10;
    int UNIQUE = 11;
    int UNIQUE = 12;
    int UNIQUE = 13;
    int UNIQUE = 14;
    int UNIQUE = 15;
    int UNIQUE = 16;
    int UNIQUE = 17;
    int UNIQUE = 18;
}
