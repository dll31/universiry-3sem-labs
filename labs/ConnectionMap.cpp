#include "ConnectionMap.h"


void ConnectionMap::addLink(int pipeId, CsConnectionData csData)
{
	links[pipeId] = csData;
}


