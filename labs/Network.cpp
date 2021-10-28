
#include <fstream>

#include "Network.h"
#include "utility.h"



void Network::loadElementsFromFile(std::string file)
{   
    int rc = 0;
    std::ifstream fin(file);
    if (fin.is_open())
    {
        std::string sep;

        while (fin.peek() != -1)
        {
            sep = "";
            rc = 0;
            Pipe p; Compressor_station cs;

            std::getline(fin, sep);

            if (sep == pipeSepInFile)
            {
                rc = p.inputFile(fin);
                if (rc == 0)
                {
                    Pipeline.insert({ p.getId(), p });
                }
            }
            else if (sep == compStationSepInFile)
            {
                rc = cs.inputFile(fin);
                if (rc == 0)
                {
                    CSArray.insert({ cs.getId(), cs });
                }
            }

            if (rc < 0)
            {
                fin.close();
                break;
            }
        }

        parseFileErrorCode(rc);
    }
    else
    {
        std::cout << "Could not open file! Try another file\n";
        return;
    }
}


void Network::pipeInputConsole()
{
    int id = getId(Pipeline);
    Pipe p(id);
    p.inputConsole();

    Pipeline.insert({ id, p });
}


void Network::csInputConsole()
{
    int id = getId(CSArray);
    Compressor_station cs(id);
    cs.inputConsole();

    CSArray.insert({ id, cs });
}


void Network::pipeEdit(int id)
{
    try
    {
        Pipeline.at(id).edit();
    }

    catch (const std::out_of_range& e)
    {
        std::cerr << "Exception at " << e.what() << '\n';
    }
}


void Network::csEdit(int id)
{
    try
    {
        CSArray.at(id).edit();
    }

    catch (const std::out_of_range& e)
    {
        std::cerr << "Exception at " << e.what() << '\n';
    }
}


void Network::pipeDeleteEnement(int id)
{
    try
    {
        Pipeline.at(id);
        Pipeline.erase(id);
    }

    catch (const std::out_of_range& e)
    {
        std::cerr << "Exception at " << e.what() << '\n';
    }
}


void Network::csDeleteEnement(int id)
{
    try
    {
        CSArray.at(id);
        CSArray.erase(id);
    }

    catch (const std::out_of_range& e)
    {
        std::cerr << "Exception at " << e.what() << '\n';
    }
}


void Network::display()
{
    std::cout << "Comprssor stations:" << '\n';
    for (auto i : CSArray)
    {
        i.second.display();
        std::cout << '\n';
    }

    std::cout << '\n' << "Pipes:" << '\n';
    for (auto i : Pipeline)
    {
        i.second.display();
        std::cout << '\n';
    }

}


template <typename itemType, typename paramType>
bool searchByName(itemType item, paramType param)
{
    return item.name == param;
}


bool searchByInRepair(const Pipe& p, bool underRepair)
{
    return p.inRepair == underRepair;
}

