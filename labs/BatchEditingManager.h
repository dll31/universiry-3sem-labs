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
