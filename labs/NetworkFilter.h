#pragma once

#include <unordered_map>
#include <vector>
#include <functional>
#include "Pipe.h"
#include "Compressor_station.h"


struct forDisabledWorkshopsFilter
{
    std::string op;
    double number;
};


static std::unordered_map<std::string, std::function<bool(double, double)> > compareOperators;

void initFilter();
void getAvailableCompareOperators(std::vector<std::string>& ops);

template<typename itemType, typename paramType>
using Filter = std::function<bool(itemType& item, paramType& param)>;

bool searchByInRepair(const Pipe& p, bool underRepair);
bool searchByPercentDisabledWorkshops(Compressor_station& cs, forDisabledWorkshopsFilter & operatorStruct);

bool searchByName(Compressor_station& item, std::string& param);


template<typename itemType, typename paramType>
std::vector<int> findIdByFilter(const std::unordered_map<int, itemType>& umap, Filter<itemType, paramType> f, paramType param)
{
    std::vector<int> filteredId;
    for (auto i : umap)
    {
        if (f(i.second, param))
            filteredId.push_back(i.first);
    }

    return filteredId;
}

