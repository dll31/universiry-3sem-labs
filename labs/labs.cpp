
#include <iostream>
#include <string>
#include <fstream>

void repairCin()
{
    std::cin.clear();
    std::cin.ignore(1000000, '\n');
}


class Pipe
{
private:
    int id = 0;
    
public:
    int diameter;
    double length;
    bool inRepair = false;
    //FIXME: fix for this labwork
    bool pipeIsEntered = false;


    void display();
    int save(std::ofstream& fout);

    void inputConsole();
    int inputFile(std::ifstream& fin);

    void edit();

    void changeInRepair();
    bool isValueInRange(int value, int from, int to);
    bool isValueInRange(double value, double from, double to);
};


void Pipe::display()
{
    std::cout << "Pipe parameters" << "\n"
        << "id: " << id << "\n"
        << "diameter: " << diameter << "\n"
        << "length: " << length << "\n"
        << "in Repair: " << (inRepair ? "True" : "False") << "\n";
}


int Pipe::save(std::ofstream& fout)
{
    if (fout.is_open())
    {
        fout << id << "\n"
            << diameter << "\n"
            << length << "\n"
            << (inRepair ? 1 : 0) << "\n";
        return 0;
    }
    return -2;
}


void Pipe::inputConsole()
{
    do
    {
        repairCin();
        std::cout << "Enter pipe diameter:\n";
        std::cin >> diameter;

    } while (std::cin.fail() || !isValueInRange(diameter, 500, 1420));

    do {
        repairCin();
        std::cout << "Enter pipe length:\n";
        std::cin >> length;
    } while (std::cin.fail());
    
    
    while (true) 
    {
        char ch;
        repairCin();
        std::cout << "Enter pipe in repair parameter (y or n):\n";
        std::cin >> ch;
        if (std::cin.fail())
            continue;

        ch = char(std::tolower(ch));
        if (ch == 'y')
        {
            inRepair = true;
            break;
        }
            
        else if (ch == 'n')
        {
            inRepair = false;
            break;
        }
    }
}


int Pipe::inputFile(std::ifstream& fin)
{
    if (fin.is_open())
    {
        fin >> id >> diameter >> length >> inRepair;
        return 0;
    }
    return -1;
}


void Pipe::edit()
{

}


void Pipe::changeInRepair()
{
    inRepair = (!inRepair);
}


bool Pipe::isValueCorrect(int from, int to)
{
    return 0;
}


class Menu
{
private:
    int menuRangeFrom = 0;
    int menuRangeTo = 7;

public:
    void showMenu();
    int getMenuValue();
    bool menuRangeCheckValue(int value);
};


void Menu::showMenu()
{
    std::cout << "1. Add pipe" << "\n"
        << "2. Add compressor station" << "\n"
        << "3. See all objects" << "\n"
        << "4. Edit pipe" << "\n"
        << "5. Edit compressor station" << "\n"
        << "6. Save" << "\n"
        << "7. Load" << "\n"
        << "0. Exit" << "\n";
}


int Menu::getMenuValue()
{
    int value = 0;
    do
    {
        repairCin();
        std::cout << "Wrong action!\n";
        std::cin >> value;
    } while (std::cin.fail() || !menuRangeCheckValue(value));

    return value;
}


bool Menu::menuRangeCheckValue(int value)
{
    if ((value >= menuRangeFrom) && (value <= menuRangeTo))
        return true;

    return false;
}


int main()
{

    Pipe* p = new Pipe;
    Menu* menu = new Menu;

    while (true)
    {
        menu->showMenu();
        std::cout << menu->getMenuValue();
    }

    //p->consoleInput();
    //p->display();
    return 0;
}