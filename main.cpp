#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <queue>
#include "Graph.h"

using namespace std;

void printArray(vector<int> array, string filePath)
{
    ofstream file(filePath, std::ios::app);

    for (int i = 0; i < array.size(); i++)
        file << array[i] << "->";

    file << endl;
    file.close();
}

void printMatrix(vector<vector<int> > matrix, string filePath)
{
    ofstream file(filePath, std::ios::app);

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
            file << (matrix[i][j] == -1 ? "" : " ") << matrix[i][j];
        file << endl;
    }
    file << endl;
    file.close();
}

void printEdge(vector<Edge> listPoint, string filePath)
{
    ofstream file(filePath, std::ios::app);

    file << "FirstPoint EndPoint Weight" << endl;
    for (int i = 0; i < listPoint.size(); i++)
    {
        file << listPoint[i].firstPoint + 1 << "          " << listPoint[i].endPoint + 1 << "        " << listPoint[i].weight << endl;
    }
    file << endl;
    file.close();
}

void printListAdjacentPoint(vector<vector<int> > listAdjacentPoint, string filePath)
{
    ofstream file(filePath, std::ios::app);

    for (int i = 0; i < listAdjacentPoint.size(); i++)
    {
        file << "Ker(" << i + 1 << ") = ";
        for (int j = 0; j < listAdjacentPoint[i].size(); j++)
            file << listAdjacentPoint[i][j] + 1 << " ";
        file << endl;
    }
    file << endl;
    file.close();
}

int main()
{
    double density = 0.2;

    string filePath20 = "directedGraph20.txt";

    Graph graph20(20, density, DIRECTED, NON_WEIGHT_MATRIX);

    vector<vector<int> > adjMatrix20 = graph20.getAdjMatrix();
    vector<vector<int> > listAdjacentPoint20 = graph20.getListAdjacentPoint();
    vector<Edge> listEdge20 = graph20.getListEdge();
    vector<vector<int> > incidenceMatrix20 = graph20.getIncidenceMatrix();
    vector<int> column20(listEdge20.size(), 0);
    vector<int> edge20(listEdge20.size(), 0);

    vector<int> dfs20ke = graph20.dfsStack(1, LIST_ADJACENT_POINT);
    cout << endl;

    vector<int> dfs20lt = graph20.dfsStack(1, INCIDENCE_MATRIX);
    cout << endl;

    vector<int> bfs20ke = graph20.bfsQueue(1, LIST_ADJACENT_POINT);
    cout << endl;

    vector<int> bfs20lt = graph20.bfsQueue(1, INCIDENCE_MATRIX);
    cout << endl;

    printMatrix(adjMatrix20, filePath20);
    printMatrix(incidenceMatrix20, filePath20);
    printEdge(listEdge20, filePath20);
    printListAdjacentPoint(listAdjacentPoint20, filePath20);
    printArray(dfs20ke, filePath20);
    printArray(dfs20lt, filePath20);
    printArray(bfs20ke, filePath20);
    printArray(bfs20lt, filePath20);

    string filePath50 = "directedGraph50.txt";

    Graph graph50(50, density, DIRECTED, NON_WEIGHT_MATRIX);

    vector<vector<int> > adjMatrix50 = graph50.getAdjMatrix();
    vector<vector<int> > listAdjacentPoint50 = graph50.getListAdjacentPoint();
    vector<Edge> listEdge50 = graph50.getListEdge();
    vector<vector<int> > incidenceMatrix50 = graph50.getIncidenceMatrix();
    vector<int> column50(listEdge50.size(), 0);
    vector<int> edge50(listEdge50.size(), 0);

    vector<int> dfs50ke = graph50.dfsStack(1, LIST_ADJACENT_POINT);
    cout << endl;

    vector<int> dfs50lt = graph50.dfsStack(1, INCIDENCE_MATRIX);
    cout << endl;

    vector<int> bfs50ke = graph50.bfsQueue(1, LIST_ADJACENT_POINT);
    cout << endl;

    vector<int> bfs50lt = graph50.bfsQueue(1, INCIDENCE_MATRIX);
    cout << endl;

    printMatrix(adjMatrix50, filePath50);
    printMatrix(incidenceMatrix50, filePath50);
    printEdge(listEdge50, filePath50);
    printListAdjacentPoint(listAdjacentPoint50, filePath50);
    printArray(dfs50ke, filePath50);
    printArray(dfs50lt, filePath50);
    printArray(bfs50ke, filePath50);
    printArray(bfs50lt, filePath50);

    string filePath100 = "directedGraph100.txt";

    Graph graph100(100, density, DIRECTED, NON_WEIGHT_MATRIX);

    vector<vector<int> > adjMatrix100 = graph100.getAdjMatrix();
    vector<vector<int> > listAdjacentPoint100 = graph100.getListAdjacentPoint();
    vector<Edge> listEdge100 = graph100.getListEdge();
    vector<vector<int> > incidenceMatrix100 = graph100.getIncidenceMatrix();
    vector<int> column100(listEdge100.size(), 0);
    vector<int> edge100(listEdge100.size(), 0);

    vector<int> dfs100ke = graph100.dfsStack(1, LIST_ADJACENT_POINT);
    cout << endl;

    vector<int> dfs100lt = graph100.dfsStack(1, INCIDENCE_MATRIX);
    cout << endl;

    vector<int> bfs100ke = graph100.bfsQueue(1, LIST_ADJACENT_POINT);
    cout << endl;

    vector<int> bfs100lt = graph100.bfsQueue(1, INCIDENCE_MATRIX);
    cout << endl;

    printMatrix(adjMatrix100, filePath100);
    printMatrix(incidenceMatrix100, filePath100);
    printEdge(listEdge100, filePath100);
    printListAdjacentPoint(listAdjacentPoint100, filePath100);
    printArray(dfs100ke, filePath100);
    printArray(dfs100lt, filePath100);
    printArray(bfs100ke, filePath100);
    printArray(bfs100lt, filePath100);

    return 0;
}