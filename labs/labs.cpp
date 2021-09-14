
#include <iostream>

struct Pipe
{
    int id;
    int d;
};


void DisplayPipe(Pipe &p)
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
}

int main()
{
    using namespace std;
    
    Pipe p = NewPipe();
    
    DisplayPipe(p);
    return 0;
}