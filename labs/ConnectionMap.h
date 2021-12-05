#pragma once

#include <unordered_map>

#include "Pipe.h"
#include "Compressor_station.h"


typedef int connectedPipeId;


struct CsLink
{
    int id;
    int workshopId;
};


struct CsConnectionData
{
    CsLink startCS;
    CsLink endCS;
};


class ConnectionMap
{
    std::unordered_map<connectedPipeId, CsConnectionData> links; // aka dumbbells


    void addLink(int pipeId, CsConnectionData csData);
};