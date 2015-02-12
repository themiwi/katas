#ifndef MAX_SPREAD_H
#define MAX_SPREAD_H

#include <cstdint>
#include <istream>
#include <list>
#include <regex>
#include <string>
#include <tuple>

// HACK around missing CYGWIN implementation
#ifdef __CYGWIN__
#include <cstdlib>
namespace std
{
inline int stoi(const std::string&& s)
{
	return strtol(s.c_str(), nullptr, 0);
}
inline float stof(const std::string&& s)
{
	return strtof(s.c_str(), nullptr);
}
}
#endif
// END HACK

inline std::list<std::tuple<uint16_t, float, float>> read_weather_data
(
	std::istream& is
)
{
	static const std::regex reg
	{
		R"(^\s*(\d+)\s+(\d+(?:\.\d*)?\*?)\s+(\d+(?:\.\d*)?\*?).*)"
	};

	std::list<std::tuple<uint16_t, float, float>> result;
	std::string line;
	while (std::getline(is, line))
	{
		std::smatch m;
		if (std::regex_match(line, m, reg))
		{
			result.push_back
			(
				std::make_tuple
				(
					uint16_t(std::stoi(m[1])),
					std::stof(m[2]),
					std::stof(m[3])
				)
			);
		}
	}
	return result;
}

template<class Iterator>
Iterator find_max_spread_element(Iterator first, Iterator last)
{
	using T = std::tuple<uint16_t, float, float>;
	return std::max_element
	(
		first,
		last,
		[](const T& r1, const T& r2)
		{
			return (std::get<1>(r1) - std::get<2>(r1))
				 < (std::get<1>(r2) - std::get<2>(r2));
		}
	);
}

///////////////////////////////////////////////////////////////////////////////

#endif // MAX_SPREAD_H
