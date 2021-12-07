#include "ConnectionMap.h"


void ConnectionMap::addLink(int pipeId, CsConnectionData csData)
{
	links[pipeId] = csData;
}


int ConnectionMap::connentParametersAvailable(int pipeId, CsConnectionData csData)
{
	if (links.count(pipeId))
		return pipeIsUnavailable;

	CsConnectionData data = links[pipeId];

	if (data.startCS.id == csData.startCS.id)
		if (data.startCS.workshopId == csData.startCS.workshopId)
			return startCsWorkshopIsUnavailable;

	if (data.endCS.id == csData.endCS.id)
		if (data.endCS.workshopId == csData.endCS.workshopId)
			return endCsWorkshopIsUnavailable;

	return available;
}

