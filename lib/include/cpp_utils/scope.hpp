/// @file on_scope_leave.hpp
/// @brief Sane way to handle C-style cleanups in C++
/// @author Wojciech Bartnik <yisonPylkita@gmail.com
///
/// Lets assume you have C-style function `int open_port(const char *port_name)`
/// and this function returns a file descriptor to opened device port. 
/// Normally you would need to write code like this
/// 
/// int port_fd = open_port("/dev/ttyUSB0");
/// try {
///     // here port_fd is beeing used
/// } catch (const std::exception &ex) {
///     close(port_fd);
///     throw ex;
/// } catch (...) {
///     close(port_fd);
///     throw "Somethig bad happend here";
/// }
/// close(port_fd);
///
/// Because of C++ exceptions you have to:
///   1) catch all exceptions
///   2) close file descriptor opened by open_port()
///   3) retrow exception
/// 
/// This approach has two major some drawbacks:
///   1) Things are getting more commplicated with every another file descriptor you need to close
///   2) You are loosing informations about exception type (or you need to 
///      write catch'es for all possible exceptions to rethrow them with the same type)
///
/// Fear not, here is the savior ^^
///
/// Just call 
///
/// #include "on_scope_leave.hpp"
///
/// on_scope_leave([port_fd] {
///     close(port_fd);
/// });
/// 
/// and the job is done. 
/// If you want to capture multiple variables you need to wrap whole lambda in parentheses:
///
/// on_scope_leave(([port_fd, &logger] {
///     close(port_fd);
///     logger->warn("I am leaving the scope");
/// }));
///
/// Yet this solution is not a silver bullet. It has one drawback - you have to be certain 
/// that lambda provided by you NEVER throws an exception. Oherwise your application will be 
/// terminated by kernel.
#pragma once
#include <functional>

#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
#define UNIQUE TOKENPASTE2(Unique_, __LINE__)


namespace on_scope_leave_impl {
/// Execute some code on scope leave
class on_scope_leave_class {
public:
    using callback = std::function<void()>;

    on_scope_leave_class(const callback &on_destroy) {
        _on_destroy = on_destroy;
    }

    // Disallow object move or copy
    on_scope_leave_class(const on_scope_leave_class &) = delete;
    on_scope_leave_class operator=(const on_scope_leave_class &) = delete;
    on_scope_leave_class(on_scope_leave_class &&) = delete;
    on_scope_leave_class operator=(on_scope_leave_class &&) = delete;

    ~on_scope_leave_class() {
        _on_destroy();
    }

private:
    callback _on_destroy;
};
}

#define on_scope_leave(callback) on_scope_leave_impl::on_scope_leave_class UNIQUE(callback)
