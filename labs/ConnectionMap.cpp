#include "ConnectionMap.h"


void ConnectionMap::addLink(int pipeId, CsConnectionData csData)
{
	links[pipeId] = csData;
}


int ConnectionMap::pipeIsAvailable(int pipeId)
{
	if (links.count(pipeId))
		return pipeIsUnavailable;

	return available;
}


int ConnectionMap::getCsBusyWorkshops(int csId)
{
	int busyWorkshops = 0;

	for (auto& i : links)
	{
		if (i.second.endCS.id == csId)
			busyWorkshops++;
		
		if (i.second.startCS.id == csId)
			busyWorkshops++;
	}

	return busyWorkshops;
}

