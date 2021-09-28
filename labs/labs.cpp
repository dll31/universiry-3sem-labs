
#include <iostream>
#include <string>
/*
struct Pipe
{
    int id;
    int d;
};*/

class Pipe 
{
private:
    int id;

public:
    int diametr;
    double length;
    bool inRepair = 0;

    void display();
    void consoleInput();
    void fileInput(std::string filePath);

};

void Pipe::display()
{
    std::cout << "Pipe parameters" << "\n"
        << "id:\t" << id << "\n"
        << "diameter:\t" << diametr << "\n"
        << "length:\t" << length << "\n"
        << "in Repair:\t" << (inRepair ? "True" : "False") << "\n";
}

void Pipe::consoleInput()
{

}

void Pipe::fileInput(std::string filePath)
{

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
    
    p->display();
    return 0;
}