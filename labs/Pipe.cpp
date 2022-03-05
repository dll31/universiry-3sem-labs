
#include <string>

#include "utility.h"
#include "Pipe.h"

Pipe::Pipe()
{
    this->id = 0;
    this->throughput = (int)round(sqrt(pow(diameter, 5) / length));
}


Pipe::Pipe(int id)
{
    this->id = id;
    this->throughput = (int)round(sqrt(pow(diameter, 5) / length));
}


void Pipe::display()
{
    std::cout << "Pipe parameters" << "\n"
        << "id: " << id << "\n"
        << "diameter: " << diameter << "\n"
        << "length: " << length << "\n"
        << "throughput: " << throughput << "\n"
        << "in Repair: " << (inRepair ? "True" : "False") << "\n";
}


int Pipe::save(std::ofstream& fout)
{
    if (fout.is_open())
    {
        fout << id << "\n"
            << diameter << "\n"
            << length << "\n"
            << throughput << "\n"
            << (inRepair ? 1 : 0) << "\n";
        return 0;
    }

    return -1;
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

        fin >> throughput;
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


void Pipe::justEdit(bool inRepair)
{
    this->inRepair = inRepair;
}


void Pipe::checkCorrectInRepairValue()
{
    inRepair = checkCorrectYorNValue("Enter pipe in repair parameter (y or n):\n");
}


int Pipe::getId()
{
    return id;
}
