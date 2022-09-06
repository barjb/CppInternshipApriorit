#ifndef _TDD_HPP_
#define _TDD_HPP_

bool IsLeapYear(unsigned int year)
{
    if (year == 0)
        return true;
    if (year % 4 != 0)
        return false;
    if (year % 100 == 0 && year % 400 != 0)
        return false;
    return true;
}

#endif