#include <iterator>

// using iteration
template<class Iterator, class T>
ptrdiff_t chop(Iterator first, Iterator last, const T& value)
{
	// Empty range, or outside of range
	if (first == last || value < *first || value > *std::prev(last))
	{
		return -1;
	}

	size_t offset = 0;
	while (first != last)
	{
		auto n = std::distance(first, last)/2;
		auto mid = std::next(first, n);
		if (value == *mid)
		{
			return offset + n;
		}
		else if (!n)
		{
			// Not found
			break;
		}
		else if (value < *mid)
		{
			last = mid;
		}
		else if (value > *mid)
		{
			first = mid;
			offset += n;
		}
		else
		{
			// This should not happen, except for floats such as
			// NaN's or Inf's or other similar cases for custom
			// types that have special values that are never <, >
			// or ==.
			break;
		}
	}
	return -1;
}

// vim: set ft=cpp :
