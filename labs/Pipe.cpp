
#include <string>

#include "Pipe.h"
#include "utility.h"


void Pipe::display()
{
    std::cout << "Pipe parameters" << "\n"
        << "id: " << id << "\n"
        << "diameter: " << diameter << "\n"
        << "length: " << length << "\n"
        << "in Repair: " << (inRepair ? "True" : "False") << "\n";
}


int Pipe::save(std::ofstream& fout)
{
    if (fout.is_open())
    {
        fout << id << "\n"
            << diameter << "\n"
            << length << "\n"
            << (inRepair ? 1 : 0) << "\n";
        return 0;
    }

    return -2;
}


void Pipe::inputConsole()
{
    while (true)
    {
        std::cout << "Enter pipe diameter:\n";
        std::cin >> diameter;

        if (std::cin.fail() || !isValueInRange(diameter, 500, 1420))
        {
            repairCin();
            continue;
        }

        break;
    }

    while (true)
    {
        std::cout << "Enter pipe length:\n";
        std::cin >> length;

        if (std::cin.fail())
        {
            repairCin();
            continue;
        }

        break;
    }

    checkCorrectInRepairValue();

    pipeIsEntered = true;
}


int Pipe::inputFile(std::ifstream& fin)
{
    if (fin.is_open())
    {
        /*If we have broken data in file, we return error*/
        fin >> id;
        if (fin.fail())
            return -2;

        fin >> diameter;
        if (fin.fail())
            return -2;

        fin >> length;
        if (fin.fail())
            return -2;

        fin >> inRepair;
        if (fin.fail())
            return -2;

        return 0;
    }

    return -1;
}


void Pipe::edit()
{
    if (!pipeIsEntered)
    {
        std::cout << "Enter pipe, before edit\n";
        return;
    }

    std::cout << "Now pipe is " << (inRepair ? "in repair" : "not in repair") << '\n';
    checkCorrectInRepairValue();
}


void Pipe::checkCorrectInRepairValue()
{
    while (true)
    {
        char ch;

        std::cout << "Enter pipe in repair parameter (y or n):\n";
        std::cin >> ch;
        if (std::cin.fail())
        {
            repairCin();
            continue;
        }

        ch = char(std::tolower(ch));
        if (ch == 'y')
        {
            inRepair = true;
            break;
        }

        else if (ch == 'n')
        {
            inRepair = false;
            break;
        }
    }
}


void Pipe::changeInRepair()
{
    inRepair = (!inRepair);
}


bool Pipe::isValueInRange(int value, int from, int to)
{
    if ((value <= to) && (value >= from))
        return true;

    return false;
}


bool Pipe::isValueInRange(double value, double from, double to)
{
    if ((value <= to) && (value >= from))
        return true;

    return false;
}
