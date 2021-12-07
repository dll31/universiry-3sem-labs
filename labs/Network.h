#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

#include "Pipe.h"
#include "Compressor_station.h"
#include "ConnectionMap.h"


class Network
{
private:
    std::string pipeSepInFile = "Pipe";
    std::string compStationSepInFile = "CS";

public:

    std::unordered_map<int, Pipe> Pipeline;
    std::unordered_map<int, Compressor_station> CSArray;

    ConnectionMap Map;

    void loadElementsFromFile(std::string file);
    void saveInFile(std::string file);

    template <typename T>
    int getId(std::unordered_map<int, T>& umap);

    void pipeInputConsole();
    void csInputConsole();

    template <typename T>
    void deleteEnement(std::unordered_map<int, T>& umap, int id);

    template <typename classType>
    void editElement(std::unordered_map<int, classType>& umap, int id);

    template <typename classType, typename userValue>
    void editAllElements(std::unordered_map<int, classType>& umap, int id, userValue& value);

    void display();

    template <typename T>
    void displayByVectorIds(std::unordered_map<int, T>& umap, std::vector<int>& vectId);

    void clearAllElements();

    //TODO:
    void connect();
    int connectParametersIsExist(int pipeId, CsConnectionData csData);
};


template <typename T>
int Network::getId(std::unordered_map<int, T>& umap)
{
    int id = 0;

    while (true)
    {
        if (!umap.count(id))
            return id;

        id++;
    }

    return id;
}


template <typename T>
void Network::deleteEnement(std::unordered_map<int, T>& umap, int id)
{
    if (umap.count(id))
        umap.erase(id);
    else
        std::cout << "No element with id " << id << "\n";
}


template <typename T>
void Network::editElement(std::unordered_map<int, T>& umap, int id)
{
    if (umap.count(id))
        umap[id].edit();
    else 
        std::cout << "No element with id " << id << "\n";
}


template <typename classType, typename userValue>
void Network::editAllElements(std::unordered_map<int, classType>& umap, int id, userValue& value)
{
    if (umap.count(id))
        umap[id].justEdit(value);
    else
        std::cout << "No element with id " << id << "\n";
}


template <typename T>
void Network::displayByVectorIds(std::unordered_map<int, T>& umap, std::vector<int>& vectId)
{
    std::cout << "\n";
    for (auto i : vectId)
    {
        if (umap.count(i))
        {
            umap[i].display();
            std::cout << "\n";
        }
        else
            std::cout << "No element with id " << i << "\n";
    }
}