#pragma once

namespace std_n {
    template <typename T>
    class range
    {
    public:
        typedef T * const_ptr;

        range(const_ptr begin, const_ptr end)
        {
            _begin = begin;
            _end = end;
        }

        const_ptr begin() const
        {
            return _begin;
        }

        const_ptr end() const
        {
            return _end;
        }

    private:
        const_ptr _begin = nullptr;
        const_ptr _end = nullptr;
    };
}