
#include "Compressor_station.h"
#include "utility.h"


void Compressor_station::display()
{
	std::cout << "Compressor station parameters:\n"
        << "id:\t" << id << '\n'
		<< "name:\t" << name << '\n'
		<< "workshops:\t" << countWorkshops << '\n'
		<< "worked workshops:\t" << countWorkedWorkshops << '\n'
		<< "performance:\t" << performance << '\n';
}


int Compressor_station::save(std::ofstream& fout)
{
    if (fout.is_open())
    {
        fout << id << '\n'
            << name << '\n'
            << countWorkshops << '\n'
            << countWorkedWorkshops << '\n'
            << performance << '\n';
        return 0;
    }

    return -2;
}


void Compressor_station::inputConsole()
{
    std::cout << "Enter compressor station name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    while (true)
    {
        std::cout << "Enter workshop count:\n";
        std::cin >> countWorkshops;

        if (std::cin.fail())
        {
            repairCin();
            continue;
        }

        break;
    }

    while (true)
    {
        std::cout << "Enter worked workshop count:\n";
        std::cin >> countWorkedWorkshops;

        if (std::cin.fail() && !isValueInRange(countWorkedWorkshops, 0, countWorkshops))
        {
            repairCin();
            continue;
        }

        break;
    }

    while (true)
    {
        std::cout << "Enter compressor station performance in range(0, 1):\n";
        std::cin >> performance;

        if (std::cin.fail() && !isValueInRange(performance, 0.0, 1.0))
        {
            repairCin();
            continue;
        }
        
        break;
    }

    //FIXME:
    compStationIsEntered = true;
}


int Compressor_station::inputFile(std::ifstream& fin)
{
    if (fin.is_open())
    {
        /*If we have broken data in file, we return error*/
        fin >> id;
        if (fin.fail())
            return -2;

        fin >> name;
        if (fin.fail())
            return -2;

        fin >> countWorkshops;
        if (fin.fail())
            return -2;

        fin >> countWorkedWorkshops;
        if (fin.fail())
            return -2;

        fin >> performance;
        if (fin.fail())
            return -2;

        return 0;
    }

    return -1;
}


void Compressor_station::startWorkshop()
{
    return;
}


void Compressor_station::stopWorkshop()
{
    return;
}


bool Compressor_station::isValueInRange(int value, int from, int to)
{
    if ((value <= to) && (value >= from))
        return true;

    return false;
}

bool Compressor_station::isValueInRange(double value, double from, double to)
{
    if ((value <= to) && (value >= from))
        return true;

    return false;
}