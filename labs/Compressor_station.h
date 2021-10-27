#pragma once

#include <iostream>
#include <fstream>
#include <string>

class Compressor_station
{
private:
	int id = 0;
public:
	std::string name;
	int countWorkshops;
	int countWorkedWorkshops;
	double performance;
    
    //FIXME: for this labwork
    bool compStationIsEntered = false;

    Compressor_station();
    Compressor_station(int id);


    void display();
    int save(std::ofstream& fout);

    void inputConsole();
    int inputFile(std::ifstream& fin);

    void changeWorkedWorkshops();
    void edit();

    int getId();
};
