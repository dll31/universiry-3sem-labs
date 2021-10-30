#pragma once

#include <unordered_map>
#include <vector>
#include "Pipe.h"
#include "Compressor_station.h"


class NetworkFilter
{
private: 
    template<typename itemType, typename paramType>
    using Filter = bool(*)(const itemType& item, paramType param);

    template <typename itemType, typename paramType>
    bool searchByName(const itemType& item, paramType param);

    bool searchByInRepair(const Pipe& p, bool underRepair);
    bool searchByPercentDisabledWorkshops(Compressor_station& cs, double percent);

    template<typename itemType, typename paramType>
    std::vector<int> FindIdByFilter(const std::unordered_map<int, itemType>& map, Filter<itemType, paramType> f, paramType param);

};


template <typename itemType, typename paramType>
bool NetworkFilter::searchByName(const itemType& item, paramType param)
{
    return item.name == param;
}


template<typename itemType, typename paramType>
std::vector<int> NetworkFilter::FindIdByFilter(const std::unordered_map<int, itemType>& map, Filter<itemType, paramType> f, paramType param)
{
    std::vector<int> filteredId;
    for (auto& i : map)
    {
        if (f(i.second, param))
            filteredId.push_back(i.second.getId());
    }

    return filteredId;
}

