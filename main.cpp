#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <queue>
#include "Graph.h"

using namespace std;

void printArray(vector<int> array)
{

    for (int i = 0; i < array.size(); i++)
        cout << array[i] << "->";

    cout << endl;
}

void printMatrix(vector<vector<int> > matrix)
{

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
            cout << (matrix[i][j] == -1 ? "" : " ") << matrix[i][j];
        cout << endl;
    }
    cout << endl;
}

void printEdge(vector<Edge> listPoint)
{

    cout << "FirstPoint EndPoint Weight" << endl;
    for (int i = 0; i < listPoint.size(); i++)
    {
        cout << listPoint[i].firstPoint + 1 << "          " << listPoint[i].endPoint + 1 << "        " << listPoint[i].weight << endl;
    }
    cout << endl;
}

void printListAdjacentPoint(vector<vector<int> > listAdjacentPoint)
{

    for (int i = 0; i < listAdjacentPoint.size(); i++)
    {
        cout << "Ker(" << i + 1 << ") = ";
        for (int j = 0; j < listAdjacentPoint[i].size(); j++)
            cout << listAdjacentPoint[i][j] + 1 << " ";
        cout << endl;
    }
    cout << endl;
}

int main()
{
    // double density = 0.2;
    // int numberOfVertex = 20;

    Graph graph("matrix.dat");
    // Graph graph(numberOfVertex, density, SCALAR, WEIGHT_MATRIX);

    vector<vector<int> > adjMatrix = graph.getAdjMatrix();
    vector<vector<int> > listAdjacentPoint = graph.getListAdjacentPoint();
    vector<Edge> listEdge = graph.getListEdge();
    // vector<vector<int> > incidenceMatrix = graph.getIncidenceMatrix();
    // vector<int> column(listEdge.size(), 0);
    // vector<int> edge(listEdge.size(), 0);
    // vector<int> bfs;

    printListAdjacentPoint(listAdjacentPoint);
    printEdge(listEdge);

    // printArray(graph.eulerianPath());

    // bfs = graph.bfsQueue(0, LIST_ADJACENT_POINT);

    // int degree = graph.deg(0);

    return 0;
}