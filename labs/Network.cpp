
#include <fstream>

#include "Network.h"
#include "utility.h"



void Network::loadElementsFromFile(std::string file)
{   
    int rc = 0;
    std::ifstream fin(file);
    if (fin.is_open())
    {
        std::string sep;

        while (fin.peek() != -1)
        {
            sep = "";
            rc = 0;
            Pipe p; Compressor_station cs;

            std::getline(fin, sep);

            if (sep == pipeSepInFile)
            {
                rc = p.inputFile(fin);
                if (rc == 0)
                {
                    Pipeline.insert({ p.getId(), p });
                }
            }
            else if (sep == compStationSepInFile)
            {
                rc = cs.inputFile(fin);
                if (rc == 0)
                {
                    CSArray.insert({ cs.getId(), cs });
                }
            }
            else if (sep == linkSepInFile)
            {
                int pipeId;
                CsConnectionData data;
                fin >> pipeId
                    >> data.startCS.id
                    >> data.endCS.id;
                Map.addLink(pipeId, data);
            }

            if (rc < 0)
            {
                fin.close();
                break;
            }
        }

        parseFileErrorCode(rc);
    }
    else
    {
        std::cout << "Could not open file! Try another file\n";
        return;
    }
}


void Network::saveInFile(std::string file)
{
    int rc = 0;
    std::ofstream fout(file);
    if (fout.is_open())
    {
        for (auto& i : Pipeline)
        {
            fout << pipeSepInFile << '\n';
            rc = i.second.save(fout);

            if (rc < 0)
                break;
        }

        rc = 0;
        for (auto& i : CSArray)
        {
            fout << compStationSepInFile << '\n';
            rc = i.second.save(fout);

            if (rc < 0)
                break;
        }

        for (auto& i : Map.links)
        {
            fout << linkSepInFile << '\n'
                << i.first << '\n'
                << i.second.startCS.id << '\n'
                << i.second.endCS.id << '\n';
        }

        fout.close();
        parseFileErrorCode(rc);

    }
    else
    {
        std::cout << "Could not open file! Try another file\n";
        return;
    }
}


void Network::pipeInputConsole()
{
    int id = getId(Pipeline);
    Pipe p(id);
    p.inputConsole();

    Pipeline.insert({ id, p });
}


void Network::csInputConsole()
{
    int id = getId(CSArray);
    Compressor_station cs(id);
    cs.inputConsole();

    CSArray.insert({ id, cs });
}


void Network::display()
{
    std::cout << "Comprssor stations:" << '\n';
    for (auto& i : CSArray)
    {
        i.second.display();
        std::cout << '\n';
    }

    std::cout << '\n' << "Pipes:" << '\n';
    for (auto& i : Pipeline)
    {
        i.second.display();
        std::cout << '\n';
    }

}


void Network::clearAllElements()
{
    Pipeline.clear();
    CSArray.clear();
    Map.clear();
}


int Network::pipeIsExist(int pipeId)
{
    if (!Pipeline.count(pipeId))
        return pipeIsUnexist;

    return exist;
}


int Network::csIsExist(int csId)
{
    if (!CSArray.count(csId))
        return csIsUnexist;

    return exist;
}


int Network::csHaveFreeWorkshop(int csId)
{
    if (CSArray[csId].getCountWorkedWorkshops() == Map.getCsBusyWorkshops(csId))
        return csWorkshopIsUnavailable;

    return have;
}


void Network::connect(int pipeId, CsConnectionData csData)
{
    Map.addLink(pipeId, csData);
}


int Network::disconnect(int pipeId)
{
    return Map.removeLink(pipeId);
}


std::vector<std::vector<int> > Network::createWeightMatrix()
{
    std::vector<std::vector<int> > matrix(CSArray.size(), std::vector<int>(CSArray.size(), std::numeric_limits<int>::max()));
    
    for (auto& pipeId : Map.links)
    {
        if (Pipeline[pipeId.first].inRepair)
            continue;

        matrix[pipeId.second.startCS.id][pipeId.second.endCS.id] = Pipeline[pipeId.first].throughput;
        matrix[pipeId.second.endCS.id][pipeId.second.startCS.id] = 0;
    }

    return matrix;
}


void Network::displayWeightMatrix()
{
    std::vector<std::vector<int> > mat = createWeightMatrix();

    for (auto& i : mat)
    {
        for (auto& j : i)
        {
            std::cout << j << " ";
        }
        std::cout << '\n';
    }
}


std::vector<int> getNeighborVertex(int pointId, std::vector<std::vector<int> >& matrix, std::deque<int>& visited)
{
    // step 2
    std::vector<int> neighborVertex;
    
    for (int i = 0; i < matrix[pointId].size(); i++)
    {
        if ((matrix[pointId][i] != std::numeric_limits<int>::max()) || (matrix[pointId][i] > 0))
        {
            bool inMarksFlag = false;
            for (auto& m : visited)
            {
                if (m == i)
                {
                    inMarksFlag = true;
                    break;
                }
            }

            if (inMarksFlag)
                continue;

            neighborVertex.push_back(i);
        }
    }

    return neighborVertex;
}

enum Ford_Fulkerson_steps
{
    init, //step 1
    getNeighbor, //step 2
    findNextPoint, // step 3
    backTotheFuture, //step 4
    recalcMatrix, //step 5
    end //step 6
};


int Network::Ford_Fulkerson_Algorithm(int startCsId, int endCsId, std::vector<std::vector<int> > weightMatrix)
{
    std::deque<int> marks, visited;
    std::vector<int> neighborVertex;
    int nowPoint, nextPoint;
    int maxFlow = 0;

    nowPoint = startCsId;
    marks.push_back(startCsId);
    visited.push_back(startCsId);

    while (true)
    {
        // step 2
        nowPoint = nextPoint;
        nextPoint = -1;
        neighborVertex = getNeighborVertex(nowPoint, weightMatrix, visited);

        if (!neighborVertex.empty())
        {
            //step 3
            int max = 0;
            int maxPointId = -1;
            for (auto& i : neighborVertex)
            {
                if (weightMatrix[nowPoint][i] > max)
                {
                    max = weightMatrix[nowPoint][i];
                    maxPointId = i;
                }
            }

            nextPoint = maxPointId;
            marks.push_back(nextPoint);
            visited.push_back(nextPoint);

            if (nextPoint == endCsId)
                //go to step 5
            else {
                // go to step 2
            }
            
        }
        else
        {
            //step 4
        }


        //step 5
        {
            int min = std::numeric_limits<int>::max();
            for (int i = 0; i < marks.size() - 1; i++)
                if (weightMatrix[marks[i]][marks[i + 1]] < min)
                    min = weightMatrix[marks[i]][marks[i + 1]];

            for (int i = 0; i < marks.size() - 1; i++)
            {
                weightMatrix[marks[i]][marks[i + 1]] -= min;
                weightMatrix[marks[i + 1]][marks[i]] += min;
            }

            maxFlow += min;
            //go to step 1
        }

        //step 4
        {
            if (nowPoint == startCsId)
            {
            }// go to step 6

            visited.push_back(nowPoint);

            nowPoint = visited[visited.size() - 2];

        }

        //step 6
        {
            return maxFlow;
        }
    }

}
