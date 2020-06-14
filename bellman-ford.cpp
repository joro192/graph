#include <iostream>
#include "Graph.h"

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

// A utility function to print the constructed distance array
void printSolution(int dist[], int previousVertex[], int size)
{
	cout << "Vertex \t\tPrevious Vertex Distance from Source\n";
	for (int i = 0; i < size; i++)
		cout << i << "\t\t" << previousVertex[i] << "\t\t" << dist[i] << endl;
}

// The main function that finds shortest distances from src to
// all other vertices using Bellman-Ford algorithm. The function
// also detects negative weight cycle
void bellmanFord(Graph graph, int src)
{
    vector<vector<int> > adjMatrix = graph.getAdjMatrix();
    vector<Edge> listEdge = graph.getListEdge();

    printMatrix(adjMatrix);

    int V = graph.size;
    int E = listEdge.size();
    int dist[V], previousVertex[V];

    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, previousVertex[i] = i;
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times. A simple shortest
    // path from src to any other vertex can have at-most |V| - 1
    // edges
    for (int i = 1; i < V; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = listEdge[j].firstPoint;
            int v = listEdge[j].endPoint;
            int weight = listEdge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v] && adjMatrix[u][v] < INT_MAX)
                dist[v] = dist[u] + weight, previousVertex[v] = u;
        }
    }

    // Step 3: check for negative-weight cycles. The above step
    // guarantees shortest distances if graph doesn't contain
    // negative weight cycle. If we get a shorter path, then there
    // is a cycle.
    for (int i = 0; i < E; i++)
    {
        int u = listEdge[i].firstPoint;
        int v = listEdge[i].endPoint;
        int weight = listEdge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v] && adjMatrix[u][v] < INT_MAX)
        {
            cout << "Graph contains negative weight cycle";
            return; // If negative cycle is detected, simply return
        }
    }

    // print the constructed distance array
	printSolution(dist, previousVertex, V);

    return;
}

void bellmanFordByListAdjPoint(Graph graph, int src)
{
    vector<vector<int> > adjMatrix = graph.getAdjMatrix();
    vector<Edge> listEdge = graph.getListEdge();
    vector<vector<int> > listAdjacentPoint = graph.getListAdjacentPoint();

    printMatrix(adjMatrix);

    int V = graph.size;
    int E = listEdge.size();
    int dist[V], previousVertex[V];

    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, previousVertex[i] = i;
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times. A simple shortest
    // path from src to any other vertex can have at-most |V| - 1
    // edges
    for (int i = 1; i < V; i++)
    {
        for (int v : listAdjacentPoint[i])
        {
            for (int u = 0; u < V; u++)
            {
                if (dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v] && adjMatrix[u][v] < INT_MAX)
                    dist[v] = dist[u] + adjMatrix[u][v], previousVertex[v] = u;
            }
        }
    }

    // Step 3: check for negative-weight cycles. The above step
    // guarantees shortest distances if graph doesn't contain
    // negative weight cycle. If we get a shorter path, then there
    // is a cycle.
    for (int i = 0; i < E; i++)
    {
        int u = listEdge[i].firstPoint;
        int v = listEdge[i].endPoint;
        int weight = listEdge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v] && adjMatrix[u][v] < INT_MAX)
        {
            cout << "Graph contains negative weight cycle";
            return; // If negative cycle is detected, simply return
        }
    }

    // print the constructed distance array
	printSolution(dist, previousVertex, V);

    return;
}

// Driver program to test above functions
int main()
{
    Graph graph("matrix.dat");

    // bellmanFord(graph, 0);
    bellmanFordByListAdjPoint(graph, 0);

    return 0;
}
