#include <iterator>

// using iteration
template<class Iterator, class T>
ptrdiff_t chop(Iterator first, Iterator last, const T& value)
{
	ptrdiff_t n = std::distance(first, last), idx = 0;
	if (!n) return -1;
	do
	{
		auto o = n / 2;
		auto mid = std::next(first, o);

		if (value == *mid)
		{
			return idx + o;
		}
		if (value < *mid)
		{
			last = mid;
		}
		else if (value > *mid)
		{
			first = mid;
			idx += o;
		}
		else
		{
			return -1;
		}
	}
	while ((n = std::distance(first, last)) > 1);
	if (n && *first == value) return idx;
	return -1;
}

// vim: set ft=cpp :
