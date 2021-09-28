
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
    bool inRepair = 0;

    void display();
    void consoleInput();
    void fileInput(const std::fstream& fin);
    void changeInRepair();
    bool isValueCorrect(int from, int to);
};

void Pipe::display()
{
    std::cout << "Pipe parameters" << "\n"
        << "id:\t" << id << "\n"
        << "diameter:\t" << diameter << "\n"
        << "length:\t" << length << "\n"
        << "in Repair:\t" << (inRepair ? "True" : "False") << "\n";
}

void Pipe::consoleInput()
{
    do
    {
        repairCin();
        std::cout << "Enter pipe diameter:\n";
        std::cin >> diameter;

    } while (std::cin.fail() || isValueCorrect(500, 1420));

    std::cout << "Enter pipe length:\n";
    std::cin >> length;
    std::cout << "Enter pipe in repair parameter (y or n):\n";
    //FIXME: not work
    //std::cin >> inRepair;

}


void Pipe::fileInput(const std::fstream& fin)
{
    if (fin.is_open())
    {
        //TODO: see file input 
        //f >> id >> 
    }

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