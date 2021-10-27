
#include <string>

#include "utility.h"
#include "Pipe.h"

Pipe::Pipe()
{
    this->id = 0;
}


Pipe::Pipe(int id)
{
    this->id = id;
}


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
    inputGoodValueFromCin("Enter pipe diameter in range(500 to 1420):\n", diameter, 500, 1420);

    inputGoodValueFromCin("Enter pipe length in meters:\n", length, 0.0, std::numeric_limits<double>::max());

    checkCorrectInRepairValue();
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
        repairCin();

        if (std::cin.fail())
            continue;

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


int Pipe::getId()
{
    return id;
}
