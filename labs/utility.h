#pragma once

#include <iostream>


enum connectionGetAccessErrors
{
    pipeIsUnavailable = -1,
    pipeIsUnexist = -2,

    csWorkshopIsUnavailable = -12,

    csIsUnexist = -13,
    csIsUnavailable = -14,

    available = 1,
    exist = 2,
    have = 3
};


void parseConnectionAccessErrors(int error);

void repairCin();


void parseFileErrorCode(int errCode);


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


bool is_digits(const std::string& str);


bool checkCorrectYorNValue(std::string messageForUser);

