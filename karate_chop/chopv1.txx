#include <iterator>

// using recursion
template<class Iterator, class T>
ptrdiff_t chop(Iterator first, Iterator last, const T& value)
{
    auto n = std::distance(first, last);

    // empty range or outside of range
    if (!n || value < *first || value > *std::prev(last)) return -1;

    // mid-point iterator
    auto offset = n / 2;
    auto mid = first;
    std::advance(mid, offset);

    if (value == *mid)
    {
        // value equal to mid-point
        return offset;
    }
    ptrdiff_t i = -1;
    if (value < *mid)
    {
        // value in first half of range
        i = chop(first, mid, value);
    }
    else if (value > *mid)
    {
        // value in second half of range
        i = chop(mid, last, value);
        if (i > -1)
        {
            i += offset;
        }
    }

    return i;
}

// vim: set ft=cpp :
