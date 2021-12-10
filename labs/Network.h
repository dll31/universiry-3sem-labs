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
    std::string linkSepInFile = "Link";

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
    void deleteElement(std::unordered_map<int, T>& umap, int id);

    template <typename classType>
    void editElement(std::unordered_map<int, classType>& umap, int id);

    template <typename classType, typename userValue>
    void editAllElements(std::unordered_map<int, classType>& umap, int id, userValue& value);

    void display();

    template <typename T>
    void displayByVectorIds(std::unordered_map<int, T>& umap, std::vector<int>& vectId);

    void clearAllElements();

    int pipeIsExist(int pipeId);
    int csIsExist(int csId);
    int csHaveFreeWorkshop(int csId);

    int connect(int pipeId, CsConnectionData csData);
    int disconnect(int pipeId);
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
void Network::deleteElement(std::unordered_map<int, T>& umap, int id)
{
    if (typeid(T) == typeid(Pipe))
    {
        if (Map.pipeIsAvailable(id) < 0)
        {
            std::cout << "disconnect pipe with id " << id << " before delete\n";
            return;
        }
    }
    else if (typeid(T) == typeid(Compressor_station))
    {
        if (Map.csIsAvailable(id) < 0)
        {
            std::cout << "disconnect CS with id " << id << " before delete\n";
            return;
        }
    }
    
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
    for (auto& i : vectId)
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