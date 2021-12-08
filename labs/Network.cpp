
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


void Network::saveInFile(std::string file)
{
    int rc = 0;
    std::ofstream fout(file);
    if (fout.is_open())
    {

        for (auto& i : Pipeline)
        {
            fout << pipeSepInFile << '\n';
            rc = i.second.save(fout);

            if (rc < 0)
                break;
        }

        rc = 0;
        for (auto& i : CSArray)
        {
            fout << compStationSepInFile << '\n';
            rc = i.second.save(fout);

            if (rc < 0)
                break;
        }

        fout.close();
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


void Network::display()
{
    std::cout << "Comprssor stations:" << '\n';
    for (auto& i : CSArray)
    {
        i.second.display();
        std::cout << '\n';
    }

    std::cout << '\n' << "Pipes:" << '\n';
    for (auto& i : Pipeline)
    {
        i.second.display();
        std::cout << '\n';
    }

}


void Network::clearAllElements()
{
    Pipeline.clear();
    CSArray.clear();
}


int Network::pipeIsExist(int pipeId)
{
    if (!Pipeline.count(pipeId))
        return pipeIsUnexist;

    return exist;
}


int Network::csIsExist(int csId)
{
    if (!CSArray.count(csId))
        return csIsUnexist;

    return exist;
}


int Network::csHaveFreeWorkshop(int csId)
{
    if (CSArray[csId].getCountWorkedWorkshops() == Map.getCsBusyWorkshops(csId))
        return csWorkshopIsUnavailable;

    return have;
}


int Network::connect(int pipeId, CsConnectionData csData)
{
    //connect
    Map.addLink(pipeId, csData);

    return 0;
}

