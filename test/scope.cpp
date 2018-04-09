#include <functional>
#include "Catch.hpp"
#include <cpp_utils/scope.hpp>

class ScopeLeaveFixture {
public:
    typedef std::function<int()> callback_type;

    ScopeLeaveFixture(callback_type call_on_destruct)
    {
        _call_on_destruct = call_on_destruct;
    }

    ~ScopeLeaveFixture()
    {
        int result = _call_on_destruct();
        set_result_code(result);
    }


    static int get_result_code()
    {
        return _result_code;
    }

private:
    static void set_result_code(int code)
    {
        _result_code = code;
    }

    static int _result_code;

private:
    std::function<int()> _call_on_destruct;
};

int ScopeLeaveFixture::_result_code = 0;

TEST_CASE("Execute some code on scope leave", "[scope]")
{
    int return_code = 0;
    {
        on_scope_leave([&return_code] {
            return_code = 1;
        });
    }
    REQUIRE(return_code == 1);
}

TEST_CASE("Multiple capture variables in lambda", "[scope]")
{
    int return_code = 0;
    int return_code_after = 0;
    {
        on_scope_leave(([&return_code, return_code_after] {
            return_code = return_code_after;
        }));
    }
    REQUIRE(return_code == return_code_after);
}

TEST_CASE("Given \"on exit\" code should be executed in reverse creation order", "[scope]")
{
    int return_code = 0;
    int return_code_control = 0;
    {
        on_scope_leave([&return_code] {
            return_code = 1;
        });

        on_scope_leave([&return_code] {
            return_code = 2;
        });

        on_scope_leave([&return_code_control] {
            return_code_control = 3;
        });
    }
    
    REQUIRE(return_code == 1);
    // To make sure that last "on exit" also was executed
    REQUIRE(return_code_control == 3); 
}
