#include "gtest/gtest.h"
#include "tdd.hpp"

TEST(leapYearTestCase, Zero)
{
    ASSERT_TRUE(IsLeapYear(0));
}

TEST(leapYearTestCase, IndivisibleByFour)
{
    ASSERT_FALSE(IsLeapYear(1));
}

TEST(leapYearTestCase, DivisibleByFour)
{
    ASSERT_TRUE(IsLeapYear(4));
}

TEST(leapYearTestCase, HundredOddMultiply)
{
    ASSERT_FALSE(IsLeapYear(100));
}

TEST(leapYearTestCase, FourHundredMultiply)
{
    ASSERT_TRUE(IsLeapYear(2000));
}