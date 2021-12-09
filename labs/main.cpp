
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


#include "Network.h"
#include "utility.h"
#include "NetworkFilter.h"
#include "BatchEditingManager.h"

bool breakOperation(int num)
{
    if (num != -1)
        return false;

    return true;
}


std::string getUserFilename()
{
    std::string filename;
    std::cout << "Enter filename with extension: ";
    std::cin.ignore();
    std::getline(std::cin, filename);

    return filename;
}


std::vector<int> getUserVectorId()
{
    std::vector<int> vectId;
    std::string str = "Enter element id. For stop enter -1\n";

    while (true)
    {
        int input = 0;
        inputGoodValueFromCin(str, input, -1, std::numeric_limits<int>::max());

        if (input == -1)
            return vectId;
        else
            vectId.push_back(input);
    }
}

template <typename vectorType>
std::string numericalVectorToString(std::vector<vectorType>& userVector)
{
    //from https://stackoverflow.com/questions/8581832/converting-a-vectorint-to-string
    std::ostringstream oss;
    
    if (!userVector.empty())
    {
        std::copy(userVector.begin(), userVector.end() - 1, std::ostream_iterator<vectorType>(oss, " "));
        oss << userVector.back();
    }

    return oss.str();
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


void menuTopSort(Network& net)
{
    net.Map.displayTopSortResult(net.Map.topologicalSort());
}

void menuDisplayConnections(Network& net)
{
    net.Map.display();
}


void menuMakeConnection(Network& net)
{

    int pipeId = -1;
    while (true)
    {
        inputGoodValueFromCin((std::string)"Enter connection pipe id or press -1 for break operation\n", pipeId, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        
        if (breakOperation(pipeId))
            return;
        
        int error = net.pipeIsExist(pipeId);
        parseConnectionAccessErrors(error);
        if (error > 0)
        {
            error = net.Map.pipeIsAvailable(pipeId);
            parseConnectionAccessErrors(error);
            if (error > 0)
                break;
        }
    }

    CsConnectionData data;
    
    while (true)
    {
        inputGoodValueFromCin((std::string)"Enter start connection cs id press -1 for break operation\n", data.startCS.id, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        
        if (breakOperation(data.startCS.id))
            return;
        
        int error = net.csIsExist(data.startCS.id);
        parseConnectionAccessErrors(error);
        if (error > 0)
        {
            error = net.csHaveFreeWorkshop(data.startCS.id);
            parseConnectionAccessErrors(error);
            if (error > 0)
                break;
        }
    }

    while (true)
    {
        inputGoodValueFromCin((std::string)"Enter end connection cs id or press -1 for break operation\n", data.endCS.id, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        
        if (breakOperation(data.endCS.id))
            return;

        if (data.startCS.id == data.endCS.id)
        {
            std::cout << "Start cs id and end cs id cant be equal\n";
            continue;
        }

        int error = net.csIsExist(data.endCS.id);
        parseConnectionAccessErrors(error);
        if (error > 0)
        {
            error = net.csHaveFreeWorkshop(data.endCS.id);
            parseConnectionAccessErrors(error);
            if (error > 0)
                break;
        }
    }

    net.connect(pipeId, data);
}


void menuNeedEditingQuestionShow()
{
    std::cout << "Do you have edit selected elements? (y or n)\n"
        << "Your answer: ";
}


bool menuNeedEditingQuestionAction()
{
    menuNeedEditingQuestionShow();
    return checkCorrectYorNValue("");
}


void menuReselectElementsShow()
{
    std::cout << "1. Continue with all selected elements\n"
        << "2. Reselect picked elements\n"
        << "Choose your action: ";
}


void menuReselectedElementsAction(std::vector<int>& vect)
{
    std::cout << "Your selected ids: " << numericalVectorToString(vect) << "\n";
    menuReselectElementsShow();

    while (true)
    {
        int action = menuInputAction();

        switch (action)
        {
        case 1:
        {
            
            return;
        }

        case 2:
        {
            std::vector<int> vectId;
            std::string str = "Enter element id. For stop enter -1\n";

            while (true)
            {
                int input = 0;
                inputGoodValueFromCin(str, input, -1, std::numeric_limits<int>::max());

                if (input == -1)
                {
                    vect = vectId;
                    break;
                }
                else
                {
                    if (std::find(vect.begin(), vect.end(), input) != vect.end())
                        vectId.push_back(input);
                    else
                        std::cout << "No such id in original ids collection.\n";
                }
            }
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


void menuBatchEditingShow()
{
    std::cout << "Input \n"
        << "1 for delete all selected elements\n"
        << "2 for edit all selected elements\n"
        << "0 exit without editing\n"
        << "Choose your action: ";
}


void menuBatchEditingAction(Network& net, std::vector<int>& vId, bool isPipeSelcted)
{
    menuBatchEditingShow();

    while (true)
    {
        int action = menuInputAction();

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
            {
                std::cout << "You need to all selected pipes be in repair(y or n): ";
                bool inRepair = checkCorrectYorNValue("");
                batchMultipleEditingById<Network, Pipe, int, bool>(net, vId, &Network::editAllElements<Pipe, bool>, net.Pipeline, inRepair);
            }
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
    pipesFilterOptionsMenuShow();

    while (true)
    {
        int action = menuInputAction();

        switch (action)
        {
        case 1:
        {
            vectId = findIdByFilter<Pipe, bool>(net.Pipeline, searchByInRepair, true);
            net.displayByVectorIds(net.Pipeline, vectId);

            if (menuNeedEditingQuestionAction())
            {
                menuReselectedElementsAction(vectId);
                menuBatchEditingAction(net, vectId, true);
            }

            return;
        }

        case 2:
        {
            vectId = findIdByFilter<Pipe, bool>(net.Pipeline, searchByInRepair, false);
            net.displayByVectorIds(net.Pipeline, vectId);
            
            if (menuNeedEditingQuestionAction())
            {
                menuReselectedElementsAction(vectId);
                menuBatchEditingAction(net, vectId, true);
            }
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


void csFilterByNameMenuAction(Network& net)
{
    csFilterByNameMenuShow();
    std::cin.ignore();

    std::string name;
    std::getline(std::cin, name);

    std::vector<int> vectId;

    vectId = findIdByFilter<Compressor_station, std::string>(net.CSArray, searchByName, name);
    net.displayByVectorIds(net.CSArray, vectId);

    if (menuNeedEditingQuestionAction())
    {
        menuReselectedElementsAction(vectId);
        menuBatchEditingAction(net, vectId, false);

    }
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
    getAvailableCompareOperators(availableCompareOperators);

    for (auto& i : availableCompareOperators)
    {
        if (bigFrase.find(i) != std::string::npos)
        {
            str.op = i;
        }
    }

    std::vector<int> vectId;
    vectId = findIdByFilter<Compressor_station, forDisabledWorkshopsFilter>(net.CSArray, searchByPercentDisabledWorkshops, str);
    net.displayByVectorIds(net.CSArray, vectId);
    
    if (menuNeedEditingQuestionAction())
    {
        menuReselectedElementsAction(vectId);
        menuBatchEditingAction(net, vectId, false);
    }
}


void filteterMenuShow()
{
    std::cout << "Search pipes by:\n"
        << "\t1. in repair parameter\n"
        << "\n Search compressor stations by:\n"
        << "\t2. name\n"
        << "\t3. percent disabled workshops\n"
        << "Other options:\n"
        << "\t0. for exit\n"
        << "Choose your action: ";
}


void filterMenuAction(Network& net)
{
    filteterMenuShow();

    while (true)
    {
        int action = menuInputAction();

        switch (action)
        {
        case 0:
        {
            return;
        }

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


void menuEditByUserShow()
{
    std::cout << "You can edit next elements\n"
        << "1 Pipes\n"
        << "2 Compressor stations\n"
        << "0 Exit\n"
        << "Choose your action: ";
}


void menuEditByUserAction(Network& net)
{
    menuEditByUserShow();
    std::vector<int> vectId;

    while (true)
    {
        int action = menuInputAction();

        switch (action)
        {
        case 0:
        {
            return;
        }

        case 1:
        {
            vectId = getUserVectorId();
            menuBatchEditingAction(net, vectId, true);
            return;
        }

        case 2:
        {
            vectId = getUserVectorId();
            menuBatchEditingAction(net, vectId, false);
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


void mainMenuShow()
{
    std::cout << "\n"
        << "1. Add pipe" << "\n"
        << "2. Add compressor station" << "\n"
        << "3. See all objects" << "\n"
        << "4. Search by filter" << "\n"
        << "5. Save" << "\n"
        << "6. Load" << "\n"
        << "7. Edit" << "\n"
        << "8. Clear all objects" << "\n"
        << "9. Create connection" << "\n"
        << "10. Display connections" << "\n"
        << "11. Top sort" << "\n"
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

        case 7:
        {
            menuEditByUserAction(net);
            break;
        }

        case 8:
        {
            net.clearAllElements();
            break;
        }

        case 9:
        {
            menuMakeConnection(net);
            break;
        }

        case 10:
        {
            menuDisplayConnections(net);
            break;
        }

        case 11:
        {
            menuTopSort(net);
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