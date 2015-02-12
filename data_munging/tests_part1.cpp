#include "part1.h"

// Work around fileno() not being defined if compiled with -std=c++11.
#ifdef __STRICT_ANSI__
#define _MUST_RESET_STRICT_ANSI_ __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include <gmock/gmock.h>
#ifdef _MUST_RESET_STRICT_ANSI_
#define __STRICT_ANSI__ _MUST_RESET_STRICT_ANSI_
#undef _MUST_RESET_STRICT_ANSI_
#endif

#include <sstream>

using namespace testing;
class weatherTest: public ::testing::Test
{
protected:
	const std::array<uint16_t, 3> days {{1, 2, 3}};
	const std::array<float, 3> max {{79, 88, 77}};
	const std::array<float, 3> min {{63, 59, 55}};
	std::stringstream data;

public:
	weatherTest()
		: data
		(
R"(
  Dy MxT   MnT   AvT   HDDay  AvDP 1HrP TPcpn WxType PDir AvSp Dir MxS SkyC MxR MnR AvSLP

   1  79    63    71          46.5       0.00         330  8.7 340  23  3.3  70 28 1004.5
   2  88*   59    74          53.8       0.00 F       280  9.6 270  17  1.6  93 23 1004.5
   3  77    55*   66          39.6       0.00         350  5.0 350   9  2.8  59 24 1016.8
  mo  82.9  60.5  71.7    16  58.8       0.00              6.9          5.3
)"
		)
	{
	}
};


TEST_F(weatherTest, returnsCorrectNumberOfRecords)
{
	auto d = read_weather_data(data);
	ASSERT_THAT(d.size(), Eq(3));
}


TEST_F(weatherTest, returnsCorrectData)
{
	auto d = read_weather_data(data);
	size_t i {0};
	for (auto r : d)
	{
		ASSERT_THAT(std::get<0>(r), Eq(days[i]));
		ASSERT_THAT(std::get<1>(r), Eq(max[i]));
		ASSERT_THAT(std::get<2>(r), Eq(min[i]));
		++i;
	}
}

TEST_F(weatherTest, findsCorrectMaxSpreadElement)
{
	auto d = read_weather_data(data);
	ASSERT_THAT(find_max_spread_element(d.begin(), d.end()), Eq(std::next(d.begin())));
}

