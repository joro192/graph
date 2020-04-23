#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

const int INCIDENCE_MATRIX = 1;
const int LIST_ADJACENT_POINT = 2;

const int SCALAR = 0;
const int DIRECTED = 1;

const int MIN_WEIGHT = 1;
const int MAX_WEIGHT = 20;

const bool WEIGHT_MATRIX = 1;
const bool NON_WEIGHT_MATRIX = 0;

struct Edge
{
    int firstPoint;
    int endPoint;
    int weight;
};

class Graph
{
public:
    Graph(int, double, int, bool);
    Graph(string);
    vector<vector<int> > getAdjMatrix();
    vector<vector<int> > convertToUnDirectedGraph();
    vector<vector<int> > getListAdjacentPoint();
    vector<vector<int> > getIncidenceMatrix();
    vector<Edge> getListEdge();
    void dfsRecusion(int, int);
    vector<int> dfsStack(int, int);
    vector<int> bfsQueue(int, int);
    vector<int> listVisitPoint;
    vector<int> listVisitEdge;

private:
    int size;
    double density;
    int numberOfEdge;
    bool isDirected;
    bool isWeight;
    vector<vector<int> > adjMatrix;
    vector<vector<int> > listAdjacentPoint;
    vector<vector<int> > incidenceMatrix;
    vector<Edge> listEdge;
};

Graph::Graph(int numberOfVertex, double ratio, int typeMatrix, bool isWeightMatrix)
{
    numberOfEdge = 0;
    size = numberOfVertex;
    vector<int> column(size, 0);
    listVisitPoint = column;
    vector<vector<int> > matrix(size, vector<int>(size, 0));
    adjMatrix = matrix;
    isWeight = isWeightMatrix;
    switch (typeMatrix)
    {
    case DIRECTED:
    {
        for (int i = 0; i < size; i++)
        {
            Edge temp;
            int weight;
            for (int j = 0; j < size; j++)
            {
                if (i == j)
                    continue;
                if (((double)(rand()) / RAND_MAX) < ratio)
                {
                    weight = rand() % MAX_WEIGHT + MIN_WEIGHT;

                    numberOfEdge++;
                    adjMatrix[i][j] = isWeightMatrix ? weight : 1;

                    temp.firstPoint = i;
                    temp.endPoint = j;
                    temp.weight = isWeightMatrix ? weight : 0;
                    listEdge.push_back(temp);
                }
            }
        }
        density = double(numberOfEdge) / (size * size);
        isDirected = true;
        vector<int> edge(numberOfEdge, 0);
        listVisitEdge = edge;
        break;
    }
    case SCALAR:
    {
        for (int i = 0; i < size; i++)
        {
            Edge temp;
            int weight;
            for (int j = i + 1; j < size; j++)
            {
                if (((double)(rand()) / RAND_MAX) < ratio)
                {
                    weight = rand() % MAX_WEIGHT + MIN_WEIGHT;

                    numberOfEdge++;
                    adjMatrix[i][j] = isWeightMatrix ? weight : 1;
                    adjMatrix[j][i] = isWeightMatrix ? weight : 1;

                    temp.firstPoint = i;
                    temp.endPoint = j;
                    temp.weight = isWeightMatrix ? weight : 0;
                    listEdge.push_back(temp);
                }
            }
        }
        density = double(2*numberOfEdge) / (size * size);
        isDirected = false;
        vector<int> edge(numberOfEdge, 0);
        listVisitEdge = edge;
        break;
    }
    default:
        break;
    }
}

Graph::Graph(string filePath)
{
    int delimiter;
    fstream input;
    input.open(filePath, ios::in);
    input >> size;
    for (int i = 0; i < size; i++)
    {
        vector<int> tempv;
        for (int j = 0; j < size; j++)
        {
            input >> delimiter;
            tempv.push_back(delimiter);
        }
        adjMatrix.push_back(tempv);
    }
}

vector<vector<int> > Graph::getAdjMatrix()
{
    return adjMatrix;
}

vector<Edge> Graph::getListEdge()
{
    return listEdge;
}

vector<vector<int> > Graph::getIncidenceMatrix()
{
    vector<vector<int> > matrix(size, vector<int>(numberOfEdge, 0));
    listEdge = getListEdge();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < numberOfEdge; j++)
        {
            matrix[i][j] = i == listEdge[j].firstPoint ? 1 : i == listEdge[j].endPoint ? isDirected ? -1 : 1 : 0;
        }
    }
    incidenceMatrix = matrix;
    return incidenceMatrix;
}

vector<vector<int> > Graph::convertToUnDirectedGraph()
{
    vector<vector<int> > adjUnDirectesMatrix = adjMatrix;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (adjMatrix[i][j] > 0)
            {
                adjUnDirectesMatrix[j][i] = adjMatrix[i][j];
            }
        }
    }
    return adjUnDirectesMatrix;
}

vector<vector<int> > Graph::getListAdjacentPoint()
{
    vector<vector<int> > adjUnDirectesMatrix = convertToUnDirectedGraph();
    for (int i = 0; i < size; i++)
    {
        vector<int> tempv;
        for (int j = 0; j < size; j++)
        {
            if (adjUnDirectesMatrix[i][j] > 0)
            {
                tempv.push_back(j);
            }
        }
        listAdjacentPoint.push_back(tempv);
    }
    return listAdjacentPoint;
}

void Graph::dfsRecusion(int startPoint, int typeMatrix)
{
    switch (typeMatrix)
    {
    case LIST_ADJACENT_POINT:
    {
        cout << startPoint + 1 << "->";

        listVisitPoint[startPoint] = 1;

        for (int i : listAdjacentPoint[startPoint])
            if (listVisitPoint[i] == 0 && adjMatrix[startPoint][i] > 0)
                dfsRecusion(i, LIST_ADJACENT_POINT);
        break;
    }
    case INCIDENCE_MATRIX:
    {
        if (!isDirected)
        {
            cout << "Not support undirected graph";
            return;
        }

        cout << startPoint + 1 << "->";

        listVisitPoint[startPoint] = 1;
        int i, j;
        // duyệt theo côt của ma trận liên thuộc (số cạnh)
        for (i = 0; i < listVisitEdge.size(); i++)
        {
            // nếu chưa thăm cạnh và cạnh chứa đỉnh thì đánh dấu đã thăm
            if (incidenceMatrix[startPoint][i] == 1 && listVisitEdge[i] == 0)
            {
                listVisitEdge[i] = 1;
                // duyệt theo hàng ma trận liên thuộc (số đỉnh)
                for (j = 0; j < listVisitPoint.size(); j++)
                {
                    // nếu là đỉnh kết thúc của cạnh thăm và đỉnh chưa được thăm thì đệ quy
                    if (incidenceMatrix[j][i] == -1 && listVisitPoint[j] == 0)
                    {
                        dfsRecusion(j, INCIDENCE_MATRIX);
                        break;
                    }
                }
            }
        }

        break;
    }
    default:
        break;
    }
}

vector<int> Graph::dfsStack(int startPoint, int typeMatrix)
{
    vector<int> dfs;
    switch (typeMatrix)
    {
    case LIST_ADJACENT_POINT:
    {

        stack<int> stackPoint;

        vector<int> column(size, 0);
        listVisitPoint = column;

        stackPoint.push(startPoint);
        cout << stackPoint.top() + 1 << "->";
        while (!stackPoint.empty())
        {
            // đánh dấu đã thăm
            listVisitPoint[stackPoint.top()] = 1;
            int count = 0;
            for (int i : listAdjacentPoint[stackPoint.top()])
                // nếu chưa thăm và tồn tại cạnh thì push vào stack
                if (listVisitPoint[i] == 0 && adjMatrix[stackPoint.top()][i] > 0)
                {
                    stackPoint.push(i);
                    cout << stackPoint.top() + 1 << "->";
                    dfs.push_back(stackPoint.top());
                    count++;
                    break;
                }
            // nếu đã thăm hết các đỉnh kề thì pop khỏi stack
            if (count == 0)
                stackPoint.pop();
        }
        break;
    }
    case INCIDENCE_MATRIX:
    {
        if (!isDirected)
        {
            cout << "Not support undirected graph";
            return dfs;
        }

        stack<int> stackPoint;

        vector<int> edge(numberOfEdge, 0);
        listVisitEdge = edge;

        vector<int> column(size, 0);
        listVisitPoint = column;

        stackPoint.push(startPoint);
        cout << stackPoint.top() + 1 << "->";
        // thăm đỉnh đầu tiên
        listVisitPoint[stackPoint.top()] = 1;

        while (!stackPoint.empty())
        {
            int i, j;
            int count = 0;
            // duyệt theo côt của ma trận liên thuộc (số cạnh)
            for (i = 0; i < listVisitEdge.size(); i++)
            {
                // nếu chưa thăm cạnh và cạnh chứa đỉnh thì đánh dấu đã thăm
                if (incidenceMatrix[stackPoint.top()][i] == 1 && listVisitEdge[i] == 0)
                {
                    listVisitEdge[i] = 1;
                    count++;
                    //duyệt theo hàng ma trận liên thuộc (số đỉnh)
                    for (j = 0; j < listVisitPoint.size(); j++)
                    {
                        // nếu là đỉnh kết thúc của cạnh thăm và đỉnh chưa được thăm thì push vào stack
                        if (incidenceMatrix[j][i] == -1 && listVisitPoint[j] == 0)
                        {
                            stackPoint.push(j);
                            listVisitPoint[stackPoint.top()] = 1;
                            cout << stackPoint.top() + 1 << "->";
                            dfs.push_back(stackPoint.top());
                            break;
                        }
                    }
                }
            }
            // nếu đã thăm hết các đỉnh kề thì pop khỏi stack
            if (count == 0)
                stackPoint.pop();
        }

        break;
    }
    default:
        break;
    }

    return dfs;
}

vector<int> Graph::bfsQueue(int startPoint, int typeMatrix)
{
    vector<int> bfs;
    switch (typeMatrix)
    {
    case LIST_ADJACENT_POINT:
    {

        queue<int> queuePoint;
        vector<int> isInQueue(size, 0);

        vector<int> column(size, 0);
        listVisitPoint = column;

        queuePoint.push(startPoint);
        isInQueue[startPoint] = 1;
        while (!queuePoint.empty())
        {
            for (int i : listAdjacentPoint[queuePoint.front()])
                if (isInQueue[i] == 0 && adjMatrix[queuePoint.front()][i] > 0)
                {
                    isInQueue[i] = 1;
                    queuePoint.push(i);
                }
            listVisitPoint[queuePoint.front()] = 1;
            cout << queuePoint.front() + 1 << "->";
            bfs.push_back(queuePoint.front());
            queuePoint.pop();
        }

        break;
    }
    case INCIDENCE_MATRIX:
    {

        if (!isDirected)
        {
            cout << "Not support undirected graph";
            return bfs;
        }
        queue<int> queuePoint;
        vector<int> isInQueue(size, 0);

        vector<int> column(size, 0);
        listVisitPoint = column;

        vector<int> edge(numberOfEdge, 0);
        listVisitEdge = edge;

        queuePoint.push(startPoint);
        // đánh dấu đỉnh bắt đầu đã vào queue
        isInQueue[startPoint] = 1;

        while (!queuePoint.empty())
        {
            int i, j;
            // duyệt theo côt của ma trận liên thuộc (số cạnh)
            for (i = 0; i < listVisitEdge.size(); i++)
            {
                // nếu chưa thăm cạnh và cạnh chứa đỉnh thì đánh dấu đã thăm
                if (incidenceMatrix[queuePoint.front()][i] == 1 && listVisitEdge[i] == 0)
                {
                    listVisitEdge[i] = 1;
                    //duyệt theo hàng ma trận liên thuộc (số đỉnh)
                    for (j = 0; j < listVisitPoint.size(); j++)
                    {
                        // nếu là đỉnh kết thúc của cạnh thăm và đỉnh chưa được thăm thì push vào queue
                        if (incidenceMatrix[j][i] == -1 && isInQueue[j] == 0)
                        {
                            // đánh dấu vào queue
                            isInQueue[j] = 1;
                            queuePoint.push(j);
                            break;
                        }
                    }
                }
            }
            listVisitPoint[queuePoint.front()] = 1;
            cout << queuePoint.front() + 1 << "->";
            bfs.push_back(queuePoint.front());
            queuePoint.pop();
        }

        break;
    }
    default:
        break;
    }
    return bfs;
}
