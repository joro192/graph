#include <iostream>
#include <vector>
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

// A structure to represent a subset for union-find
class subset
{
public:
    int parent;
    int rank;
};

// A utility function to find set of an element i
// (uses path compression technique)
int find(subset subsets[], int i)
{
    // find root and make root as parent of i
    // (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;

    // If ranks are same, then make one as root and
    // increment its rank by one
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int myComp(Edge a, Edge b)
{
    return a.weight < b.weight;
}

void kruskal(Graph graph)
{
    vector<Edge> listEdge = graph.getListEdge();

    int numberOfVertex = graph.size;
    int numberOfEdge = listEdge.size();
    Edge result[numberOfVertex]; // Tnis will store the resultant MST

    // sort edge order by weight
    sort(listEdge.begin(), listEdge.end(), myComp);

    subset *subsets = new subset[(numberOfVertex * sizeof(subset))];

    // Create V subsets with single elements
    for (int v = 0; v < numberOfVertex; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int e = 0; // An index variable, used for result[]
    int i = 0; // An index variable, used for sorted edges

    // Number of edges to be taken is equal to V-1
    while (e < numberOfVertex - 1 && i < numberOfEdge)
    {
        // Step 2: Pick the smallest edge. And increment
        // the index for next iteration
        Edge next_edge = listEdge[i++];

        int x = find(subsets, next_edge.firstPoint);
        int y = find(subsets, next_edge.endPoint);

        // If including this edge does't cause cycle,
        // include it in result and increment the index
        // of result for next edge
        if (x != y)
        {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
        // Else discard the next_edge
    }

    // print the contents of result[] to display the
    // built MST
    cout << "Minimum spanning tree\n";
    int weight = 0;
    for (i = 0; i < e; ++i)
    {
        cout << "(" << result[i].firstPoint << "," << result[i].endPoint << ")-";
        weight += result[i].weight;
    }
    cout << " Total weight: " << weight << endl;
    return;
}

int main()
{
    int numberOfVertex = 20;
    double density = 0.18;

    Graph graph(numberOfVertex, density, SCALAR, WEIGHT_MATRIX);

    // Graph graph("matrix.dat");

    vector<vector<int> > adjMatrix = graph.getAdjMatrix();

    printMatrix(adjMatrix);

    kruskal(graph);

    return 0;
}