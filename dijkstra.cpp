// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph

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

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[], int size)
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < size; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

// A utility function to print the constructed distance array
void printSolution(int dist[], int previousVertex[], int size)
{
	cout << "Vertex \t\tPrevious Vertex Distance from Source\n";
	for (int i = 0; i < size; i++)
		cout << i << "\t\t" << previousVertex[i] << "\t\t" << dist[i] << endl;
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(vector<vector<int> > adjMatrix, int src)
{
	// Number of vertices in the graph
	int V = adjMatrix.size();

	// previous vertex
	int previousVertex[V];

	int dist[V]; // The output array. dist[i] will hold the shortest
	// distance from src to i

	bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
	// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false, previousVertex[i] = i;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in the first iteration.
		int u = minDistance(dist, sptSet, V);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < V; v++)

			// Update dist[v] only if is not in sptSet, there is an edge from
			// u to v, and total weight of path from src to v through u is
			// smaller than current value of dist[v]
			if (!sptSet[v] && adjMatrix[u][v] && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v] && adjMatrix[u][v] < INT_MAX)
				dist[v] = dist[u] + adjMatrix[u][v], previousVertex[v] = u;
	}

	// print the constructed distance array
	printSolution(dist, previousVertex, V);
}

// using listAdjPoint
void dijkstraByListAdjPoint(vector<vector<int> > adjMatrix, vector<vector<int> > listAdjacentPoint, int src)
{
	// Number of vertices in the graph
	int V = adjMatrix.size();

	// previous vertex
	int previousVertex[V];

	int dist[V]; // The output array. dist[i] will hold the shortest
	// distance from src to i

	bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
	// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false, previousVertex[i] = i;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in the first iteration.
		int u = minDistance(dist, sptSet, V);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v : listAdjacentPoint[u])

			// Update dist[v] only if is not in sptSet, there is an edge from
			// u to v, and total weight of path from src to v through u is
			// smaller than current value of dist[v]
			if (!sptSet[v] && adjMatrix[u][v] && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v] && adjMatrix[u][v] < INT_MAX)
				dist[v] = dist[u] + adjMatrix[u][v], previousVertex[v] = u;
		;
	}

	// print the constructed distance array
	printSolution(dist, previousVertex, V);
}

// driver program to test above function
int main()
{
	Graph graph("matrix.dat");

	vector<vector<int> > adjMatrix = graph.getAdjMatrix();
	vector<vector<int> > listAdjacentPoint = graph.getListAdjacentPoint();

	printMatrix(adjMatrix);
	printMatrix(listAdjacentPoint);

	dijkstraByListAdjPoint(adjMatrix, listAdjacentPoint, 2);
	// dijkstra(adjMatrix, 2);

	return 0;
}
