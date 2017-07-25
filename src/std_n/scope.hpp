#pragma once

///
/// Execute some code on scope leave
/// 

#include <functional>
#include <pro_utils/preprocessor.hpp>

namespace pro_utils {
namespace impl {
/// <summary>
/// Execute some code on scope leave
/// </summary>
class on_scope_leave_class {
public:
    using callback = std::function<void()>;

    on_scope_leave_class(const callback &on_destroy)
    {
        _on_destroy = on_destroy;
    }

    // Disallow object move or copy
    on_scope_leave_class(const on_scope_leave_class &) = delete;
    on_scope_leave_class operator=(const on_scope_leave_class &) = delete;
    on_scope_leave_class(on_scope_leave_class &&) = delete;
    on_scope_leave_class operator=(on_scope_leave_class &&) = delete;

    ~on_scope_leave_class()
    {
        _on_destroy();
    }

private:
    callback _on_destroy;
};
}
}

/// <summary>
/// Execute code all scope leave
/// </summary>
/// <remarks>
/// 1) on_scope_leave will be called in reverse order of construction
/// 2) if you want to pass multiple values is lambda capture you need to wrap whole lambda in parentheses
/// Example:
/// 
///     on_scope_leave(([b, &a] {
///         a = b;
///     }));
/// </remarks>
#define on_scope_leave(callback) pro_utils::impl::on_scope_leave_class UNIQUE(callback)
