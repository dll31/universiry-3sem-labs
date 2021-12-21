
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


static std::vector<int> getNeighborVertexes(int pointId, std::vector<std::vector<int> >& matrix, std::deque<int>& visited)
{
    std::vector<int> neighborVertexes;
    
    for (int i = 0; i < matrix[pointId].size(); i++)
    {
        if ((matrix[pointId][i] != std::numeric_limits<int>::max()) && (matrix[pointId][i] > 0))
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

            neighborVertexes.push_back(i);
        }
    }

    return neighborVertexes;
}


enum Ford_Fulkerson_steps 
{
    init, //step 1
    getNeighbor, //step 2
    findNextPoint, // step 3
    backToTheFuture, //step 4
    recalcMatrix, //step 5
    end //step 6
};


int Network::Ford_Fulkerson_Algorithm(int startCsId, int endCsId, std::vector<std::vector<int> > weightMatrix)
{
    std::deque<int> marks, visited;
    std::vector<int> neighborVertexes;
    int nowPoint, nextPoint;
    int maxFlow = 0;

    Ford_Fulkerson_steps step = init;

    while (true)
    {
        switch (step)
        {
        case(init):
        {
            marks.clear();
            visited.clear();
            
            nowPoint = startCsId;
            marks.push_back(startCsId);
            visited.push_back(startCsId);
            
            step = getNeighbor;
            break;
        }

        case(getNeighbor):
        {
            neighborVertexes = getNeighborVertexes(nowPoint, weightMatrix, visited);

            if (!neighborVertexes.empty())
                step = findNextPoint;
            else
                step = backToTheFuture;

            break;
        }

        case(findNextPoint):
        {
            int max = 0;
            int maxPointId = -1;
            for (auto& i : neighborVertexes)
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

            nowPoint = nextPoint;

            if (nextPoint == endCsId)
                step = recalcMatrix;
            else 
                step = getNeighbor;

            break;
        }

        case(backToTheFuture):
        {
            if (nowPoint == startCsId)
            {
                step = end;
                break;
            }

            auto elemPos = std::find(marks.begin(), marks.end(), nowPoint);
            if (elemPos != marks.end())
                marks.erase(elemPos);

            nowPoint = visited[visited.size() - 2];

            step = getNeighbor;
            break;
        }

        case(recalcMatrix):
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
            
            step = init;
            break;
        }

        case(end):
        {
            return maxFlow;
        }

        }
    }
}

//from https://github.com/BelovitskiyDA/Shortcut
static void findWay(std::vector<std::vector <double>>& matrix, std::vector<double>& vectWeight, int startPoint, int endPoint)
{
    std::stack <int> way;
    int workPoint = endPoint;
    int n = matrix.size();
    int k = 0;
    way.push(endPoint);
    double weight = vectWeight[endPoint];
    while (workPoint != startPoint && k <= n)
    {
        for (int i = 0; i < n; i++)
        {
            if (matrix[i][workPoint] != 0 && matrix[i][workPoint] != std::numeric_limits<double>::infinity())
            {

                if (weight - matrix[i][workPoint] == vectWeight[i])
                {
                    weight = weight - matrix[i][workPoint];
                    workPoint = i;
                    way.push(workPoint);

                }
            }
        }
        k++;
    }

    if (k > n)
        std::cout << "error find way" << '\t';
    else
    {
        while (!way.empty())
        {
            std::cout << way.top() << " ";
            way.pop();
        }
        std::cout << '\t';
    }
}


//from https://github.com/BelovitskiyDA/Shortcut
void Network::algorithmDijkstra(std::vector<std::vector <double>> matrix, int startPoint, int endPoint) {
    /*std::cout << "Dijkstra's algorithm start: " << std::endl;*/
    std::size_t n = matrix.size();
    std::vector<double> min_weight(n, std::numeric_limits<double>::infinity());
    min_weight[startPoint] = 0;
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            if (matrix[i][j] < 0) {
                /*std::cout << "Dijkstra's algorithm works only for graphs without edges of negative weight" << std::endl;*/
                std::cout << "Dijkstra: error" << '\t';
                return;
            }
            else if (matrix[i][j] == 0) {
                matrix[i][j] = std::numeric_limits<double>::infinity();
            }
        }
    }

    auto start = std::chrono::system_clock::now();

    std::priority_queue<std::pair <double, int>> q_vertices;
    q_vertices.push({ 0, startPoint });
    while (!q_vertices.empty()) {
        double len = -q_vertices.top().first;
        int vertex = q_vertices.top().second;
        q_vertices.pop();
        if (len > min_weight[vertex]) {
            continue;
        }
        for (std::size_t i = 0; i < n; ++i) {
            size_t to = i;
            double length_vert_to = matrix[vertex][to];
            if (min_weight[to] > min_weight[vertex] + length_vert_to) {
                min_weight[to] = min_weight[vertex] + length_vert_to;
                q_vertices.push({ -min_weight[to], to });
            }
        }
    }
    /*cout << "Answer = " << min_weight[endPoint] << endl;*/
    std::cout << "Dijkstra: " << min_weight[endPoint] << '\t';

    //auto finish = chrono::system_clock::now();
    //auto duration = chrono::duration_cast<chrono::nanoseconds>(finish - start).count(); //milliseconds nanoseconds
    //cout << "time(nanoseconds) : " << duration << '\t';
    /*cout << duration << ", ";*/

    findWay(matrix, min_weight, startPoint, endPoint);
}
