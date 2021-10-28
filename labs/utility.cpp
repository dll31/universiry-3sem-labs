
#include "utility.h"
#include <string.h>

void repairCin()
{
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}


void parseFileErrorCode(int errCode)
{
    if (errCode == 0)
    {
        std::cout << "Succesfull operation!\n";
    }
    else
    {
        if (errCode == -1)
        {
            std::cout << "Could not open file!\n";
        }
        else if (errCode == -2)
        {
            std::cout << "Broken data in file!\n";
            //TODO: try to write exception in cout
        }
        else
        {
            std::cout << "Unexpected error code: " << errCode << '\n';
        }
    }
}