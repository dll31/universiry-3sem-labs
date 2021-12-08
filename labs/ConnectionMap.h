#pragma once

#include <unordered_map>

#include "Pipe.h"
#include "Compressor_station.h"
#include "utility.h"


typedef int connectedPipeId;


struct CsLink
{
    int id;
    //int workshopId;
};


struct CsConnectionData
{
    CsLink startCS;
    CsLink endCS;
};


class ConnectionMap
{
    std::unordered_map<connectedPipeId, CsConnectionData> links; // aka dumbbells

public:
    void addLink(int pipeId, CsConnectionData csData);

    int connentParametersAvailable(int pipeId, CsConnectionData csData);
    int getCsBusyWorkshops(int csId);

    int pipeIsAvailable(int pipeId);

    int csIsAvailable(int csId);

};