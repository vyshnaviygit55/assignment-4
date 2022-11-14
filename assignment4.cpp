#include <bits/stdc++.h>
using namespace std;

int NO_PARENT = -1;

void printPath(int currentVertex, vector<int> parents)
{

    if (currentVertex == NO_PARENT) {
        return;
    }
    printPath(parents[currentVertex], parents);
    cout << currentVertex << " ";
}

void printSolution(int startVertex, vector<int> distances,
                vector<int> parents)
{
    int nVertices = distances.size();
    cout << "Vertex\t Distance\tPath";

    for (int vertexIndex = 0; vertexIndex < nVertices;
        vertexIndex++) {
        if (vertexIndex != startVertex) {
            cout << "\n" << startVertex << " -> ";
            cout << vertexIndex << " \t\t ";
            cout << distances[vertexIndex] << "\t";
            printPath(vertexIndex, parents);
        }
    }
}

void dijkstra(vector<vector<int> > adjacencyMatrix,
            int startVertex)
{
    int nVertices = adjacencyMatrix[0].size();
    vector<int> shortestDistances(nVertices);
    vector<bool> added(nVertices);

    for (int vertexIndex = 0; vertexIndex < nVertices;
        vertexIndex++) {
        shortestDistances[vertexIndex] = INT_MAX;
        added[vertexIndex] = false;
    }

    shortestDistances[startVertex] = 0;
    vector<int> parents(nVertices);
    parents[startVertex] = NO_PARENT;
    for (int i = 1; i < nVertices; i++) {
        int nearestVertex = -1;
        int shortestDistance = INT_MAX;
        for (int vertexIndex = 0; vertexIndex < nVertices;
            vertexIndex++) {
            if (!added[vertexIndex]
                && shortestDistances[vertexIndex]
                    < shortestDistance) {
                nearestVertex = vertexIndex;
                shortestDistance
                    = shortestDistances[vertexIndex];
            }
        }
        added[nearestVertex] = true;

        for (int vertexIndex = 0; vertexIndex < nVertices;
            vertexIndex++) {
            int edgeDistance
                = adjacencyMatrix[nearestVertex]
                                [vertexIndex];

            if (edgeDistance > 0
                && ((shortestDistance + edgeDistance)
                    < shortestDistances[vertexIndex])) {
                parents[vertexIndex] = nearestVertex;
                shortestDistances[vertexIndex]
                    = shortestDistance + edgeDistance;
            }
        }
    }

    printSolution(startVertex, shortestDistances, parents);
}

int main()
{
    vector<vector<int> > adjacencyMatrix
        = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
            { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
            { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
            { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
            { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
            { 0, 0, 4, 0, 10, 0, 2, 0, 0 },
            { 0, 0, 0, 14, 0, 2, 0, 1, 6 },
            { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
            { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
    int source, end; 
    cout <<"Select the start node: ";
    cin>>source;
    cout <<"Select the end node: ";
    cin>>end;
    dijkstra(adjacencyMatrix, source);
    return 0;
}
