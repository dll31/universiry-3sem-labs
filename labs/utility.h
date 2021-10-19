#pragma once

#include <iostream>

void repairCin();


template <typename T>
bool isValueInRange(const T& value, T from, T to)
{
    if ((value <= to) && (value >= from))
        return true;

    return false;
}


template <typename T>
void inputGoodValueFromCin(std::string stringToUser, T& inputValue, const T valueRangeFrom, const T valueRangeTo)
{
    while (true)
    {
        std::cout << stringToUser;
        std::cin >> inputValue;

        if (std::cin.fail() || !isValueInRange(inputValue, valueRangeFrom, valueRangeTo))
        {
            repairCin();
            continue;
        }

        repairCin();
        break;
    }
    return;
}


