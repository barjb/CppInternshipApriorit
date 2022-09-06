#include <iostream>
#include "gtest/gtest.h"
#include "lib.hpp"

TEST(productsAmountTestCase, emptyVector)
{
    std::vector<int> m{};
    int amount = 1;
    EXPECT_EQ(GetProductsAmount(m, amount), 0);
}

TEST(productsAmountTestCase, oneLenNegative)
{
    std::vector<int> m{0};
    int amount = 1;
    EXPECT_EQ(GetProductsAmount(m, amount), 1);
}

TEST(productsAmountTestCase, oneLenPositive)
{
    std::vector<int> m{2};
    int amount = 1;
    EXPECT_EQ(GetProductsAmount(m, amount), 0);
}

TEST(productsAmountTestCase, twoLenPositive)
{
    std::vector<int> m{13, 9};
    int amount = 1;
    EXPECT_EQ(GetProductsAmount(m, amount), 0);
}

TEST(productsAmountTestCase, twoLenNegative)
{
    std::vector<int> m{13, 9};
    int amount = 30;
    EXPECT_EQ(GetProductsAmount(m, amount), 2);
}

TEST(productsAmountTestCase, threeLenMiddle)
{
    std::vector<int> m{13, 9, 10};
    int amount = 17;
    EXPECT_EQ(GetProductsAmount(m, amount), 1);
}