
#include "utility.h"
#include <string>

void repairCin()
{
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}


bool isValueInRange(const int & value, int from, int to)
{
    if ((value <= to) && (value >= from))
        return true;

    return false;
}


bool isValueInRange(const double & value, double from, double to)
{
    if ((value <= to) && (value >= from))
        return true;

    return false;
}


