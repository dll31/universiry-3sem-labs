#pragma once

#include <iostream>
#include <unordered_map>

#include "Pipe.h"
#include "Compressor_station.h"


class Network
{
private:
    std::string pipeSepInFile = "Pipe";
    std::string compStationSepInFile = "CS";

public:

    std::unordered_map<int, Pipe> Pipeline;
    std::unordered_map<int, Compressor_station> CSArray;

    void loadElementsFromFile(std::string file);
    template <typename T>
    int getId(T& map);

    void pipeInputConsole();
    void csInputConsole();

    void pipeEdit(int id);
    void csEdit(int id);

    void pipeDeleteEnement(int id);
    void csDeleteEnement(int id);

    void display();
};


template <typename T>
int Network::getId(T& map)
{
    int id = 0;

    while (true)
    {
        //from example: https://www.geeksforgeeks.org/unordered_map-at-cpp/
        try
        {
            map.at(id);
        }

        catch (const std::out_of_range& e)
        {
            return id;
        }

        id++;
    }

    return id;
}
