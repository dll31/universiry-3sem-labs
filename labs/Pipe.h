#pragma once

#include <iostream>
#include <fstream>

class Pipe
{
private:
    int id = 0;

public:
    //std::string name;
    int diameter;
    double length;
    bool inRepair = false;


    void display();
    int save(std::ofstream& fout);

    void inputConsole();
    int inputFile(std::ifstream& fin);

    void edit();

    void checkCorrectInRepairValue();
};