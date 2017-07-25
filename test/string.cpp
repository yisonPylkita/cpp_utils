#include <test/Catch.hpp>
#include <pro_utils/string.hpp>

namespace str = pro_utils::string;
using pro_utils::string::string;

TEST_CASE("One letter to_lower()", "[string]")
{
    REQUIRE(str::to_lower(_T("A")) == _T("a"));
}

TEST_CASE("One letter to_lower() (already in lower-case)", "[string]")
{
    REQUIRE(str::to_lower(_T("a")) == _T("a"));
}

TEST_CASE("Empty string passed to to_lower() results in empty string", "[string]")
{
    REQUIRE(str::to_lower(_T("")) == _T(""));
}

TEST_CASE("Multiple characters", "[string]")
{
    string before = _T("1fE638b478F8f0b2c2aab3bdfd3f05F6dfe2191cd7B4482241fE58567e37aef6");
    string expected_after = _T("1fe638b478f8f0b2c2aab3bdfd3f05f6dfe2191cd7b4482241fe58567e37aef6");
    REQUIRE(str::to_lower(before) == expected_after);
}

TEST_CASE("On empty string should return empty string", "[string]")
{
    REQUIRE(str::replace_all(_T(""), _T("C"), _T("#1")) == _T(""));
}

TEST_CASE("On empty string should return empty string (case-insensitive)", "[string]")
{
    REQUIRE(str::replace_all(_T(""), _T("C"), _T("#1"), str::CaseSensitivity::insensitive) == _T(""));
}

TEST_CASE("Should work with string with one entry to replace", "[string]")
{
    string before = _T("A");
    string expected = _T("B%");
    REQUIRE(str::replace_all(before, _T("A"), _T("B%")) == expected);
}

TEST_CASE("Should work with string with one entry to replace (case-insensitive)", "[string]")
{
    string before = _T("a");
    string expected = _T("B%");
    REQUIRE(str::replace_all(before, _T("A"), _T("B%"), str::CaseSensitivity::insensitive) == expected);
}

TEST_CASE("Should work with string with multiple entries to replace", "[string]")
{
    string before = _T(" CAbC55CCC6 6#CC@ !C!C");
    string expected = _T(" #1Ab#155#1#1#16 6##1#1@ !#1!#1");
    REQUIRE(str::replace_all(before, _T("C"), _T("#1")) == expected);
}

TEST_CASE("Should work with string with multiple entries to replace (case-insensitive)", "[string]")
{
    string before = _T(" cABc55CcC6 6#Cc@ !c!c");
    string expected = _T(" #1AB#155#1#1#16 6##1#1@ !#1!#1");
    REQUIRE(str::replace_all(before, _T("C"), _T("#1"), str::CaseSensitivity::insensitive) == expected);
}

TEST_CASE("On empty string relpace_begin() should return empty string", "[string]")
{
    REQUIRE(str::replace_begin(_T(""), _T("C"), _T("#1")) == _T(""));
}

TEST_CASE("On empty string replace_begin() should return empty string (case-insensitive)", "[string]")
{
    REQUIRE(str::replace_begin(_T(""), _T("C"), _T("#1"), str::CaseSensitivity::insensitive) == _T(""));
}

TEST_CASE("replace_begin() should work with string with one entry to replace", "[string]")
{
    string before = _T("A");
    string expected = _T("B%");
    REQUIRE(str::replace_begin(before, _T("A"), _T("B%")) == expected);
}

TEST_CASE("replace_begin should work with string with one entry to replace (case-insensitive)", "[string]")
{
    string before = _T("a");
    string expected = _T("B%");
    REQUIRE(str::replace_begin(before, _T("A"), _T("B%"), str::CaseSensitivity::insensitive) == expected);
}

TEST_CASE("Only first occurence should be replaced", "[string]")
{
    string before = _T(R"(C:\Foo\Boo.txt)");
    string expected = _T(R"(C:\Goo\Boo.txt)");
    REQUIRE(str::replace_begin(before, _T("C:\\Foo"), _T("C:\\Goo")) == expected);
}

TEST_CASE("Only first occurence should be replaced (case-insensitive)", "[string]")
{
    string before = _T(R"(C:\Foo\Boo.txt)");
    string expected = _T(R"(C:\Goo\Boo.txt)");
    REQUIRE(str::replace_begin(before, _T("C:\\Foo"), _T("C:\\Goo"), str::CaseSensitivity::insensitive) == expected);
}

TEST_CASE("replace_begin() should return the same when there is no string to replace", "[string]")
{
    string before = _T("xyz");
    string expected = _T("xyz");
    REQUIRE(str::replace_begin(before, _T("C"), _T("#1")) == expected);
}

TEST_CASE("replace_begin should return the same when there is no string to replace (case-insensitive)", "[string]")
{
    string before = _T("xyz");
    string expected = _T("xyz");
    REQUIRE(str::replace_begin(before, _T("C"), _T("#1"), str::CaseSensitivity::insensitive) == expected);
}

TEST_CASE("Should return original string when no occurencess of searched string were found", "[string]")
{
    REQUIRE(str::replace_all(_T("C"), _T("#1"), _T("#2")) == _T("C"));
}
