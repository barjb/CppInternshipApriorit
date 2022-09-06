#ifndef _lib_hpp_
#define _lib_hpp_

#include <iostream>
#include <vector>
#include <algorithm>

int GetProductsAmount(std::vector<int> &prices, int amountOfMoney)
{
    std::sort(prices.begin(), prices.end());

    int sum = 0;
    for (int i = 0; i < prices.size(); ++i)
    {
        sum += prices[i];
        if (sum > amountOfMoney)
        {
            return i;
        }
    }
    return prices.size();
}

#endif