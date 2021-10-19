
#include <fstream>

#include "Network.h"



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
            std::getline(fin, sep);

            if (sep == pipeSepInFile)
            {
                p.pipeIsEntered = false;
                rc = p.inputFile(fin);
            }
            else if (sep == compStationSepInFile)
            {
                cs.compStationIsEntered = false;
                rc = cs.inputFile(fin);
            }

            if (rc < 0)
            {
                fin.close();
                break;
            }
        }

        if (rc == 0)
        {
            std::cout << "Succesfull loading!\n";
            p.pipeIsEntered = true;
            cs.compStationIsEntered = true;
        }
        else
        {
            if (rc == -1)
            {
                std::cout << "Could not open file!\n";
            }
            else if (rc == -2)
            {
                std::cout << "Broken data in file!\n";
                //TODO: try to write exception in cout
            }
            else
            {
                std::cout << "Unexpected error code: " << rc << '\n';
            }
        }
    }
    else
    {
        std::cout << "Could not open file! Try another file\n";
        return;
    }
}