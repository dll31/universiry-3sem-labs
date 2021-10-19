
#include <iostream>
#include <string>
#include <fstream>

#include "Pipe.h"
#include "Compressor_station.h"
#include "utility.h"

// TODO: in Network class

class Network
{
private:
    std::string pipeSepInFile = "Pipe";
    std::string compStationSepInFile = "CS";

public:
    Pipe p;
    Compressor_station cs;

    void loadElementsFromFile(std::string file);
};



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
                /*rc = loadPipeFromFile();*/
                p.pipeIsEntered = false;// FIXME: something like this
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


//FIXME: function for this labwork
void savePipeInFile(std::string file, Pipe& p)
{    
    if (!p.pipeIsEntered)
    {
        std::cout << "Enter pipe, before save\n";
        return;
    }

    int rc = 0;
    
    std::ofstream fout(file);

    if (fout.is_open())
    {
        rc = p.save(fout);
        fout.close();
    }
    else
    {
        std::cout << "Try another file\n";
        return;
    }

    if (rc == 0)
    {
        std::cout << "Pipe saved\n";
        return;
    }

    std::cout << "Something wrong\n";
}


//FIXME: function for this labwork
void saveCompStaitionInFile(std::string file, Compressor_station& cs)
{
    if (!cs.compStationIsEntered)
    {
        std::cout << "Enter compressor station, before save\n";
        return;
    }

    int rc = -1;
    std::ofstream fout(file);

    if (fout.is_open())
    {
        rc = cs.save(fout);
        fout.close();
    }
    else
    {
        std::cout << "Try another file\n";
        return;
    }

    if (rc == 0)
    {
        std::cout << "Compressor station saved\n";
        return;
    }

    std::cout << "Something wrong\n";
}


void showMenu()
{
    std::cout << "\n" 
        << "1. Add pipe" << "\n"
        << "2. Add compressor station" << "\n"
        << "3. See all objects" << "\n"
        << "4. Edit pipe" << "\n"
        << "5. Edit compressor station" << "\n"
        << "6. Save" << "\n"
        << "7. Load" << "\n"
        << "0. Exit" << "\n"
        << "Choose your action: ";
}


int main()
{  
    Network net;
    

    while (true)
    {
        showMenu();
        int action = -1;
        while (true)
        {
            std::cin >> action;

            if (std::cin.fail())
            {
                repairCin();
                std::cout << "Wrong action\n";
                showMenu();
                continue;
            }
                

            break;
        }

        switch (action)
        {
        case 1:
        {
            net.p.inputConsole();
            break;
        }

        case 2:
        {
            net.cs.inputConsole();
            break;
        }

        case 3:
        {
            if (net.p.pipeIsEntered)
                net.p.display();

            if (net.cs.compStationIsEntered)
                net.cs.display();
            break;
        }

        case 4:
        {
            net.p.edit();
            break;
        }

        case 5:
        {
            net.cs.changeWorkedWorkshops();
            break;
        }

        case 6:
        {
            savePipeInFile("data_pipe.txt", net.p);
            saveCompStaitionInFile("data_cs.txt", net.cs);
            break;
        }

        case 7:
        {
            net.loadElementsFromFile("data.txt");
            break;
        }

        case 0:
        {
            return 0;
        }

        default: 
        {
            std::cout << "Wrong action\n";
        }
        }
    }

    return 0;
}