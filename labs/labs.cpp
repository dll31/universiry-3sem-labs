
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
    void fileInput(const std::fstream & f);

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
    std::cout << "Enter pipe diameter:\n";
    std::cin >> diameter;
    std::cout << "Enter pipe length:\n";
    std::cin >> length;
    std::cout << "Enter pipe in repair parameter (y or n):\n";
    //FIXME: not work
    //std::cin >> inRepair;
    
}


void Pipe::fileInput(const std::fstream & f)
{

    if (f.is_open())
    {
        //TODO: see file input 
        //f >> id >> 
    }

}

/*
void DisplayPipe(const Pipe &p)
{
    std::cout << "Pipe id:\t" << p.id << "\n"
        << "Pipe diameter:\t" << p.d;
}


Pipe NewPipe()
{
    Pipe p = { 0 }; 
    std::cout << "Enter pipe diameter\n";
    std::cin >> p.d;

    return p;
}*/

int main()
{
    
    Pipe *p = new Pipe;
    p->consoleInput();
    p->display();
    return 0;
}