
#include <iostream>
#include <string>
#include <fstream>

#include "Network.h"
#include "utility.h"



//FIXME: function for this labwork
void savePipeInFile(std::string file, Pipe& p)
{    
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
            net.pipeInputConsole();
            break;
        }

        case 2:
        {
            net.csInputConsole();
            break;
        }

        case 3:
        {
            net.display();
            break;
        }

        case 4:
        {
            //net.pipeEdit();
            break;
        }

        case 5:
        {
            //net.csEdit();
            break;
        }

        case 6:
        {
            //savePipeInFile("data_pipe.txt", net.p);
            //saveCompStaitionInFile("data_cs.txt", net.cs);
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