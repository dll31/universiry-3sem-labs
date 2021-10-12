#pragma once

#include <iostream>
#include <fstream>

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


    void checkCorrectInRepairValue();
    void changeInRepair();
    ///////////????????????????
    bool isValueInRange(int value, int from, int to);
    bool isValueInRange(double value, double from, double to);
};