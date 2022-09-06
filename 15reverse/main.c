#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main()
{
    srand(time(0));
    int a, b, c, d, e, f;

    int sumAF = 222;
    int sumBE = 209;
    int sumCD = 212;
    int maxASCII = 126;

    a = sumAF - maxASCII + rand() % (2 * maxASCII - sumAF + 1);
    b = sumBE - maxASCII + rand() % (2 * maxASCII - sumBE + 1);
    c = sumCD - maxASCII + rand() % (2 * maxASCII - sumCD + 1);
    d = sumCD - c;
    e = sumBE - b;
    f = sumAF - a;

    printf("%c%c%c%c%c%c\n", a, b, c, d, e, f);
}