
#include <iostream>
#include <string>
#include <fstream>

#include "Network.h"
#include "utility.h"


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

std::string getUserFilename()
{
    std::string filename;
    std::cout << "Enter filename with extension: ";
    std::cin.ignore();
    std::getline(std::cin, filename);

    return filename;
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
            net.saveInFile(getUserFilename());
            break;
        }

        case 7:
        {
            net.loadElementsFromFile(getUserFilename());
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