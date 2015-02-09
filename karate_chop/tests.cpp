#if defined(USE_V1)
#include "chopv1.txx"
#elif defined(USE_V2)
#include "chopv2.txx"
#else
#error USE_VXXX (XXX being an integer) not defined.
#endif

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

#include <string>
#include <array>

using namespace testing;

///////////////////////////////////////////////////////////////////////////////

TEST(chopTest, emptyRangeReturnsMinusOne)
{
	std::array<int, 0> a {};
	ASSERT_THAT(chop(a.begin(), a.end(), 3), Eq(-1));
}

TEST(chopTest, notInRangeReturnsMinusOne)
{
	std::array<int, 1> a {1};
	ASSERT_THAT(chop(a.begin(), a.end(), 3), Eq(-1));
}

TEST(chopTest, matchWithSingleElementInRangeReturnsZero)
{
	std::array<int, 1> a {1};
	ASSERT_THAT(chop(a.begin(), a.end(), 1), Eq(0));
}

///////////////////////////////////////////////////////////////////////////////

struct chopTestThreeElements : public ::testing::Test
{
protected:
	std::array<int, 3> a;
public:
	chopTestThreeElements()
		: a { 1, 3, 5 }
	{
		/* empty */
	}
};

TEST_F(chopTestThreeElements, matchFirstElementReturnsZero)
{
	ASSERT_THAT(chop(a.begin(), a.end(), a[0]), Eq(0));
}

TEST_F(chopTestThreeElements, matchSecondElementReturnsOne)
{
	ASSERT_THAT(chop(a.begin(), a.end(), a[1]), Eq(1));
}

TEST_F(chopTestThreeElements, matchThirdElementReturnsTwo)
{
	ASSERT_THAT(chop(a.begin(), a.end(), a[2]), Eq(2));
}

TEST_F(chopTestThreeElements, tryFindBeforeFirstElementReturnsMinusOne)
{
	ASSERT_THAT(chop(a.begin(), a.end(), 0), -1);
}

TEST_F(chopTestThreeElements, tryFindBetweenElementsReturnsMinusOne)
{
	ASSERT_THAT(chop(a.begin(), a.end(), 2), -1);
	ASSERT_THAT(chop(a.begin(), a.end(), 4), -1);
}

TEST_F(chopTestThreeElements, tryFindAfterLastElementReturnsMinusOne)
{
	ASSERT_THAT(chop(a.begin(), a.end(), 6), -1);
}

///////////////////////////////////////////////////////////////////////////////

struct chopTestFourElements : public ::testing::Test
{
protected:
	std::array<int, 4> a;
public:
	chopTestFourElements()
		: a { 1, 3, 5, 7 }
	{
		/* empty */
	}
};

TEST_F(chopTestFourElements, matchFirstElementReturnsZero)
{
	ASSERT_THAT(chop(a.begin(), a.end(), a[0]), Eq(0));
}

TEST_F(chopTestFourElements, matchSecondElementReturnsOne)
{
	ASSERT_THAT(chop(a.begin(), a.end(), a[1]), Eq(1));
}

TEST_F(chopTestFourElements, matchThirdElementReturnsTwo)
{
	ASSERT_THAT(chop(a.begin(), a.end(), a[2]), Eq(2));
}

TEST_F(chopTestFourElements, matchFourthElementReturnsThree)
{
	ASSERT_THAT(chop(a.begin(), a.end(), a[3]), Eq(3));
}

TEST_F(chopTestFourElements, tryFindBeforeFirstElementReturnsMinusOne)
{
	ASSERT_THAT(chop(a.begin(), a.end(), 0), -1);
}

TEST_F(chopTestFourElements, tryFindBetweenElementsReturnsMinusOne)
{
	ASSERT_THAT(chop(a.begin(), a.end(), 2), -1);
	ASSERT_THAT(chop(a.begin(), a.end(), 4), -1);
	ASSERT_THAT(chop(a.begin(), a.end(), 6), -1);
}

TEST_F(chopTestFourElements, tryFindAfterLastElementReturnsMinusOne)
{
	ASSERT_THAT(chop(a.begin(), a.end(), 8), -1);
}
