
#include "utility.h"
#include <string.h>

void repairCin()
{
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}
