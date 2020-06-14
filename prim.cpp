#include <iostream>
#include "Graph.h"

using namespace std;

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

// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(int key[], bool mstSet[], int size)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < size; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

// A utility function to print the
// constructed MST stored in parent[]
void printMST(int parent[], vector<vector<int> > adjMatrix)
{
    cout << "Edge \tWeight\n";
    for (int i = 1; i < adjMatrix.size(); i++)
        cout << parent[i] << " - " << i << " \t" << adjMatrix[i][parent[i]] << " \n";
}

// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
void primMST(Graph graph)
{
    vector<vector<int> > adjMatrix = graph.getAdjMatrix();

    printMatrix(adjMatrix);

    // check connected graph
    if (!graph.isConnected())
    {
        cout << "Not support unconnected graph"<< endl;
        return;
    }

    int V = adjMatrix.size();
    // Array to store constructed MST
    int parent[V];

    // Key values used to pick minimum weight edge in cut
    int key[V];

    // To represent set of vertices included in MST
    bool mstSet[V];

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false, parent[i] = i;

    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex.
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum key vertex from the
        // set of vertices not yet included in MST
        int u = minKey(key, mstSet, V);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST
        for (int v = 0; v < V; v++)

            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (adjMatrix[u][v] && mstSet[v] == false && adjMatrix[u][v] < key[v])
                parent[v] = u, key[v] = adjMatrix[u][v];
    }

    // print the constructed MST
    cout << "Minimum spanning tree\n";
    int weight = 0;
    for (int i = 1; i < V; ++i)
    {
        cout << "(" << parent[i] << "," << i << ")-";
        weight += adjMatrix[i][parent[i]];
    }
    cout << " Total weight: " << weight << endl;
    return;
}

// Driver code
int main()
{
    // int numberOfVertex = 20;
    // double density = 0.18;

    // Graph graph(numberOfVertex, density, SCALAR, WEIGHT_MATRIX);

    Graph graph("matrix.dat");

    primMST(graph);

    return 0;
}
