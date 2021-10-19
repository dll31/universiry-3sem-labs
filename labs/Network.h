#pragma once

#include <iostream>

#include "Pipe.h"
#include "Compressor_station.h"


class Network
{
private:
    std::string pipeSepInFile = "Pipe";
    std::string compStationSepInFile = "CS";

public:
    Pipe p;
    Compressor_station cs;

    void loadElementsFromFile(std::string file);
};
