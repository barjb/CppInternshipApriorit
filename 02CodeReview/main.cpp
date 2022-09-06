#include "MyVector.hpp"
#include <iostream>
#include <utility>
#include <string>

int main()
{
    std::cout << "====N====\n";

    cnntrs::MyVector<int> n{};
    n.push_back(0, "zero");
    n.push_back(1, "jeden");

    // auto x = n[0];
    // std::cout << x.first << ", " << x.second << std::endl;
    // auto y = n[1];
    // std::cout << y.first << ", " << y.second << std::endl;

    auto z = n["zero"];
    std::cout << z << std::endl;
    auto c = n["jeden"];
    std::cout << c << std::endl;

    try
    {
        auto ex = n[-1];
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        auto ex = n["dwa"];
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    auto it = n.begin();
    auto end = n.end();

    std::cout << "elemns\n";
    for (; it != end; it++)
    {
        auto &elem = *it;
        std::cout << elem << std::endl;
    }

    auto cit = n.cbegin();
    auto cend = n.cend();

    std::cout << "celemns\n";
    for (; cit != cend; cit++)
    {
        auto &elem = *cit;
        std::cout << elem << std::endl;
    }

    std::cout << "is empty: " << n.empty() << std::endl;
    std::cout << "size: " << n.size() << std::endl;
    n.clear();
    std::cout << "is empty: " << n.empty() << std::endl;
    std::cout << "size: " << n.size() << std::endl;
    // std::cout << "====M====\n";
    // cnntrs::MyVector<int> m(n);
    // n.push_back(3, "trzy");
    // {
    //     cnntrs::MyVector<int> p(n);
    //     cnntrs::MyVector<int> o(n);
    //     m.push_back(2, "dwa");
    //     n.push_back(33, "e");
    //     {
    //         cnntrs::MyVector<int> k(n);
    //         {
    //             cnntrs::MyVector<int> l(n);
    //         }
    //     }
    // }
}