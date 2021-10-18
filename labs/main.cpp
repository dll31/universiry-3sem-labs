
#include <iostream>
#include <string>
#include <fstream>

#include "Pipe.h"
#include "Compressor_station.h"
#include "utility.h"


//FIXME: function for this labwork
void loadPipeFromFile(std::string file, Pipe& p)
{
    int rc = -1;
    std::ifstream fin(file);
    if (fin.is_open())
    {
        p.pipeIsEntered = false;
        rc = p.inputFile(fin);
        fin.close();
    }
    else
    {
        std::cout << "Try another file\n";
        return;
    }

    if (rc == 0)
    {
        p.pipeIsEntered = true;
        std::cout << "Pipe loaded\n";
        return;
    }
    else if (rc == -2)
    {
        std::cout << "Broken data in file. File path: " << file << '\n';
        return;
    }
    
    std::cout << "Something wrong\n";
}

//FIXME: function for this labwork
void savePipeInFile(std::string file, Pipe& p)
{
    if (!p.pipeIsEntered)
    {
        std::cout << "Enter pipe, before save\n";
        return;
    }

    int rc = -1;
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
void loadCompStationFromFile(std::string file, Compressor_station& cs)
{
    int rc = -1;
    std::ifstream fin(file);
    if (fin.is_open())
    {
        cs.compStationIsEntered = false;
        rc = cs.inputFile(fin);
        fin.close();
    }
    else
    {
        std::cout << "Try another file\n";
        return;
    }

    if (rc == 0)
    {
        cs.compStationIsEntered = true;
        std::cout << "Compressor station loaded\n";
        return;
    }
    else if (rc == -2)
    {
        std::cout << "Broken data in file. File path: " << file << '\n';
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
    Pipe p;
    Compressor_station cs;
    

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
            p.inputConsole();
            break;
        }

        case 2:
        {
            cs.inputConsole();
            break;
        }

        case 3:
        {
            if (p.pipeIsEntered)
                p.display();

            if (cs.compStationIsEntered)
                cs.display();
            break;
        }

        case 4:
        {
            p.edit();
            break;
        }

        case 5:
        {
            cs.changeWorkedWorkshops();
            break;
        }

        case 6:
        {
            savePipeInFile("data_pipe.txt", p);
            saveCompStaitionInFile("data_cs.txt", cs);
            break;
        }

        case 7:
        {
            loadPipeFromFile("data_pipe.txt", p);
            loadCompStationFromFile("data_cs.txt", cs);
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