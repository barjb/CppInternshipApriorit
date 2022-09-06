#include <iostream>
#include "md5.h"

// using std::cout;
// using std::endl;

// #include <stdlib.h>
// #include <time.h>
// #include <stdio.h>
#include <charconv>
#include <string>

int main(int argc, char *argv[])
{
    srand(time(0));
    int a, b, c, d, e, f;

    int sumAF = 222;
    int sumBE = 209;
    int sumCD = 212;
    int maxASCII = 126;

    // a = sumAF - maxASCII + rand() % (2 * maxASCII - sumAF + 1);
    // b = sumBE - maxASCII + rand() % (2 * maxASCII - sumBE + 1);
    // c = sumCD - maxASCII + rand() % (2 * maxASCII - sumCD + 1);
    // d = sumCD - c;
    // e = sumBE - b;
    // f = sumAF - a;

    int startA = 96;
    int startB = 83;
    int startC = 86;
    std::string result = "96c4dda0c4a0b34262b1d91d47056f9e";

    for (int i = startA; i <= maxASCII; ++i)
    {
        for (int j = startB; j <= maxASCII; ++j)
        {
            for (int k = startC; k <= maxASCII; ++k)
            {
                a = i;
                b = j;
                c = k;
                d = sumCD - c;
                e = sumBE - b;
                f = sumAF - a;
                std::string temp{};
                std::cout << a << ", " << b << ", " << c << ", " << d << ", " << e << ", " << f << std::endl;
                temp.push_back(char(a));
                temp.push_back(char(b));
                temp.push_back(char(c));
                temp.push_back(char(d));
                temp.push_back(char(e));
                temp.push_back(char(f));
                std::cout << temp << std::endl;
                std::string temp2 = md5(temp);
                if (result.compare(temp2) == 0)
                {
                    std::cout << "FINISH\n";
                    std::cout << temp << std::endl;
                    return 1;
                }
            }
        }
    }

    return 0;
}