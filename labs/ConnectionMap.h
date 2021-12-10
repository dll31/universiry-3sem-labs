#pragma once

#include <unordered_map>
#include <map>
#include <stack>

#include "Pipe.h"
#include "Compressor_station.h"
#include "utility.h"

typedef int connectedPipeId;

enum color
{
    black = 0,
    gray = 1,
    white = 2,
};


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
    void dfs(int v, std::map<int, color>& visited, std::stack<int>& out);

public:

    std::unordered_map<connectedPipeId, CsConnectionData> links; // aka dumbbells

    void addLink(int pipeId, CsConnectionData csData);
    int removeLink(int pipeId);

    int getCsBusyWorkshops(int csId);

    int pipeIsAvailable(int pipeId);
    int csIsAvailable(int csId);

    void display();

    void displayTopSortResult(std::stack<int> res);

    std::stack<int> topologicalSort();

    void clear();
};