
#include "utility.h"


void repairCin()
{
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "FAIL!\n";
}