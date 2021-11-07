#pragma once

#include <unordered_map>
#include <vector>
#include <functional>
#include "Pipe.h"
#include "Compressor_station.h"


class NetworkFilter
{
public:
    template<typename itemType, typename paramType>
    using Filter = std::function<bool(const itemType& item, const paramType& param)>;

    template <typename itemType, typename paramType>
    bool searchByName(const itemType& item, paramType param);

    bool searchByInRepair(const Pipe& p, bool underRepair);
    bool searchByPercentDisabledWorkshops(Compressor_station& cs, double percent);

    template<typename itemType, typename paramType>
    std::vector<int> findIdByFilter(const std::unordered_map<int, itemType>& map, Filter<itemType, paramType> f, paramType param);

};


template <typename itemType, typename paramType>
bool NetworkFilter::searchByName(const itemType& item, paramType param)
{
    return item.name == param;
}


template<typename itemType, typename paramType>
std::vector<int> NetworkFilter::findIdByFilter(const std::unordered_map<int, itemType>& map, Filter<itemType, paramType> f, paramType param)
{
    std::vector<int> filteredId;
    for (auto i : map)
    {
        if (f(i.second, param))
            filteredId.push_back(i.second.getId());
    }

    return filteredId;
}

