// A C++ program for Bellman-Ford's single source
// shortest path algorithm.
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

/* A utility function to print solution */
void printSolution(vector<vector<int> > dist)  
{  
    cout<<"The following matrix shows the shortest distances"
            " between every pair of vertices \n";  
    for (int i = 0; i < dist.size(); i++)  
    {  
        for (int j = 0; j < dist[i].size(); j++)  
        {  
            if (dist[i][j] == INT_MAX)  
                cout<<"INF"<<"     ";  
            else
                cout<<dist[i][j]<<"     ";  
        }  
        cout<<endl;  
    }  
}  

// The main function that finds shortest distances from src to
// all other vertices using Floyd algorithm. The function
// also detects negative weight cycle
void floydWarshall(Graph graph)
{
    vector<vector<int> > adjMatrix = graph.getAdjMatrix();

    printMatrix(adjMatrix);

    int V = graph.size;
    vector<vector<int> > dist(V, vector<int>(V, INT_MAX));
    int i, j, k;

    // Step 1: Initialize distances 
    for (i = 0; i < V; i++)  
        for (j = 0; j < V; j++)  
            dist[i][j] = i == j ? 0 : adjMatrix[i][j];

    // Step 2: Add all vertices one by one to  
    // the set of intermediate vertices.  
    // ---> Before start of an iteration,  
    // we have shortest distances between all  
    // pairs of vertices such that the  
    // shortest distances consider only the  
    // vertices in set {0, 1, 2, .. k-1} as 
    // intermediate vertices.  
    // ----> After the end of an iteration,  
    // vertex no. k is added to the set of  
    // intermediate vertices and the set becomes {0, 1, 2, .. k} 

    for (k = 0; k < V; k++)  
    {  
        // Pick all vertices as source one by one  
        for (i = 0; i < V; i++)  
        {  
            // Pick all vertices as destination for the  
            // above picked source  
            for (j = 0; j < V; j++)  
            {  
                // If vertex k is on the shortest path from  
                // i to j, then update the value of dist[i][j]  
                if (dist[i][k] + dist[k][j] < dist[i][j] && dist[i][k] < INT_MAX && dist[k][j] < INT_MAX)  
                    dist[i][j] = dist[i][k] + dist[k][j];  
            }  
        }  
    }  
  
    // Print the shortest distance matrix  
    printSolution(dist);  

    return;
}

void floydWarshallByListAdjPoint(Graph graph)
{
    vector<vector<int> > adjMatrix = graph.getAdjMatrix();
    vector<vector<int> > listAdjacentPoint = graph.getListAdjacentPoint();

    // printMatrix(adjMatrix);

    int V = graph.size;
    vector<vector<int> > dist(V, vector<int>(V, INT_MAX));

    // Step 1: Initialize distances 
    for (int i = 0; i < V; i++)  
        for (int j = 0; j < V; j++)  
            dist[i][j] = i != j ? adjMatrix[i][j] : 0;

    // Step 2: Add all vertices one by one to  
    // the set of intermediate vertices.  
    // ---> Before start of an iteration,  
    // we have shortest distances between all  
    // pairs of vertices such that the  
    // shortest distances consider only the  
    // vertices in set {0, 1, 2, .. k-1} as 
    // intermediate vertices.  
    // ----> After the end of an iteration,  
    // vertex no. k is added to the set of  
    // intermediate vertices and the set becomes {0, 1, 2, .. k} 

    for (int k = 0; k < V; k++)  
    {  
        // Pick all vertices as source one by one  
        for (int i = 0; i < V; i++)  
        {  
            // Pick all vertices as destination for the  
            // above picked source  
            for (int j : listAdjacentPoint[i])  
            {  
                // If vertex k is on the shortest path from  
                // i to j, then update the value of dist[i][j]  
                if (dist[i][k] + dist[k][j] < dist[i][j] && dist[i][k] < INT_MAX && dist[k][j] < INT_MAX)    
                    dist[i][j] = dist[i][k] + dist[k][j];  
            }  
        }  
    }  
  
    // Print the shortest distance matrix  
    printSolution(dist);  

    return;
}


// Driver program to test above functions
int main()
{
    Graph graph("matrix.dat");
    
    // floydWarshall(graph);
    floydWarshallByListAdjPoint(graph);

    return 0;
}
