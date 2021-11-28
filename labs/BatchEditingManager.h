#pragma once


#include <unordered_map>
#include <functional>

#include "Network.h"


template <typename classType, typename itemType, typename paramType>
using editFunction = std::function<void(classType& self, std::unordered_map<int, itemType>& umap, paramType& param)>;

template<typename classType, typename itemType, typename paramType>
void batchEditingById(classType& self, std::vector<int>& vectId, editFunction<classType, itemType, paramType> f, std::unordered_map<int, itemType>& umap)
{
	for (auto i : vectId)
	{
		f(self, umap, i);
	}
}


template <typename classType, typename itemType, typename paramType, typename userValue>
using editMultipleFunction = std::function<void(classType& self, std::unordered_map<int, itemType>& umap, paramType& param, userValue& value)>;

template<typename classType, typename itemType, typename paramType, typename userValue>
void batchMultipleEditingById(classType& self, std::vector<int>& vectId, editMultipleFunction<classType, itemType, paramType, userValue> f, std::unordered_map<int, itemType>& umap, userValue& value)
{
	for (auto i : vectId)
	{
		f(self, umap, i, value);
	}
}
