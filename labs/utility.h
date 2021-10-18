#pragma once

#include <iostream>

void repairCin();

bool isValueInRange(const int& value, int from, int to);
bool isValueInRange(const double& value, double from, double to);

template <typename T>
void inputGoodValueFromCin(std::string stringToUser, T& inputValue, const T valueRangeFrom, const T valueRangeTo)
{
    while (true)
    {
        std::cout << stringToUser;
        std::cin >> inputValue;
        repairCin();

        if (std::cin.fail() || !isValueInRange(inputValue, valueRangeFrom, valueRangeTo))
            continue;

        break;
    }
    return;
}
