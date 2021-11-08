
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Network.h"
#include "utility.h"
#include "NetworkFilter.h"
#include "BatchEditingManager.h"


std::string getUserFilename()
{
    std::string filename;
    std::cout << "Enter filename with extension: ";
    std::cin.ignore();
    std::getline(std::cin, filename);

    return filename;
}


int menuInputAction()
{
    int action = -1;
    while (true)
    {
        std::cin >> action;

        if (std::cin.fail())
        {
            repairCin();
            std::cout << "Wrong action\n";
            continue;
        }

        return action;
    }
}


void menuNeedEditingQuestionShow()
{
    std::cout << "Do you have edit selected elements? (y or n)\n"
        << "Your answer: ";
}


bool menuNeedEditingQuestionAction()
{
    menuNeedEditingQuestionShow();
    return checkCorrectYonNValue("");
}


void menuBatchEditingShow()
{
    std::cout << "Input \n"
        << "1 for delete all selected elements\n"
        << "2 for edit all selected elements\n"
        << "0 exit without editing\n"
        << "Choose your action: ";
}


void menuBatchEditingActoin(Network& net, std::vector<int>& vId, bool isPipeSelcted)
{
    menuBatchEditingShow();
    int action = menuInputAction();

    while (true)
    {
        switch (action)
        {
        case 1:
        {
            if (isPipeSelcted)
                batchEditingById<Network, Pipe, int>(net, vId, &Network::deleteEnement<Pipe>, net.Pipeline);
            else 
                batchEditingById<Network, Compressor_station, int>(net, vId, &Network::deleteEnement<Compressor_station>, net.CSArray);
            return;
        }

        case 2:
        {
            if (isPipeSelcted)
                batchEditingById<Network, Pipe, int>(net, vId, &Network::editElement<Pipe>, net.Pipeline);
            else
                batchEditingById<Network, Compressor_station, int>(net, vId, &Network::editElement<Compressor_station>, net.CSArray);
            return;
        }
        
        case 0:
        {
            return;
        }

        default:
        {
            std::cout << "Wrong action!";
            break;
        }
        }
    }
}


void pipesFilterOptionsMenuShow()
{
    std::cout << "Input:\n"
        << "1 if you need all pipes in repair\n"
        << "2 if you need all pipes in work\n"
        << "Choose your action: ";
}


void pipesFilterOptionsAction(Network& net)
{
    std::vector<int> vectId;

    while (true)
    {
        pipesFilterOptionsMenuShow();
        int action = menuInputAction();

        switch (action)
        {
        case 1:
        {
            vectId = findIdByFilter<Pipe, bool>(net.Pipeline, searchByInRepair, true);
            if (menuNeedEditingQuestionAction())
                menuBatchEditingActoin(net, vectId, true);
            return;
        }

        case 2:
        {
            vectId = findIdByFilter<Pipe, bool>(net.Pipeline, searchByInRepair, false);
            if (menuNeedEditingQuestionAction())
                menuBatchEditingActoin(net, vectId, true);
            return;
        }

        default:
        {
            std::cout << "Wrong action\n";
            break;
        }
        }
    }
}


void csFilterByNameMenuShow()
{
    std::cout << "Enter compressor station name:\n";
}


void csFilterByNameMenuAction(Network & net)
{
    csFilterByNameMenuShow();
    std::cin.ignore();

    std::string name;
    std::getline(std::cin, name);

    std::vector<int> vectId;

    vectId = findIdByFilter<Compressor_station, std::string>(net.CSArray, searchByName, name);
    if (menuNeedEditingQuestionAction())
        menuBatchEditingActoin(net, vectId, false);
}


void csFilterByPercentDisWsMenuShow()
{
    std::cout << "You have next magic keywords for operators: less, greather, equal, not equal, greather equal, less equal.\n"
        << "For example, if you need compressor stations where percent disabled workshops less and equal 60,\n you need to write: \" "
        << "less equal 60\" without quotes.\n"
        << "Print your frase: ";
}


void csFilterByPercentDisWsMenuAction(Network& net)
{
    std::string frase, bigFrase = "";
    
    csFilterByPercentDisWsMenuShow();
    std::cin.ignore();
    std::getline(std::cin, frase);

    std::stringstream ss(frase);
    forDisabledWorkshopsFilter str;

    while (ss.peek() != -1)
    {
        ss >> frase;
        if (is_digits(frase))
            str.number = std::stoi(frase);
        else
            bigFrase += (" " + frase);
    }

    std::vector<std::string> availableCompareOperators;
    if (menuNeedEditingQuestionAction())
        getAvailableCompareOperators(availableCompareOperators);

    for (auto i : availableCompareOperators)
    {
        if (bigFrase.find(i) != std::string::npos)
        {
            str.op = i;
        }
    }

    std::vector<int> vectId;
    vectId = findIdByFilter<Compressor_station, forDisabledWorkshopsFilter>(net.CSArray, searchByPercentDisabledWorkshops, str);
    menuBatchEditingActoin(net, vectId, false);
}


void filteterMenuShow()
{
    std::cout << "Search pipes by:\n"
        << "\t1. in repair parameter\n"
        << "\n Search compressor stations by:\n"
        << "\t2. name\n"
        << "\t3. percent disabled workshops\n"
        << "Choose your action: ";
}


void filterMenuAction(Network& net)
{
    while (true)
    {
        filteterMenuShow();
        int action = menuInputAction();

        switch (action)
        {
        case 1:
        {
            pipesFilterOptionsAction(net);
            return;
        }

        case 2:
        {
            csFilterByNameMenuAction(net);
            return;
        }

        case 3:
        {
            csFilterByPercentDisWsMenuAction(net);
            return;
        }

        default:
            std::cout << "Wrong action\n";
            break;
        }
    }
}


void mainMenuShow()
{
    std::cout << "\n"
        << "1. Add pipe" << "\n"
        << "2. Add compressor station" << "\n"
        << "3. See all objects" << "\n"
        << "4. Search by filter" << "\n"
        << "5. Save" << "\n"
        << "6. Load" << "\n"
        << "0. Exit" << "\n"
        << "Choose your action: ";
}


int main()
{  
    Network net;
    initFilter();

    while (true)
    {        
        mainMenuShow();
        int action = menuInputAction();

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
            filterMenuAction(net);
            break;
        }

        case 5:
        {   
            net.saveInFile(getUserFilename());
            break;
        }

        case 6:
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