#pragma once

#include <iostream>


enum connectionGetAccessErrors
{
    pipeIsUnavailable = -1,
    pipeIsUnexist = -2,

    startCsWorkshopIsUnavailable = -12,
    
    startCsIsUnexist = -13,
    startCsWorkshopIsUnexist = -14,

    endCsWorkshopIsUnavailable = -22,
    
    endCsIsUnexist = -23,
    endCsWorkshopIsUnexist = -24,
    
    available = 1,
    exist = 1
};


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

