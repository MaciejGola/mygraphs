#pragma once

#include <iostream>
#include <vector>
using namespace std;

void addEdge(vector<int> adjList[], int u, int v)
{
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

void printVertexes(int vertexes)
{
    cout << "Liczba wierzcholkow grafu G wynosi: " << vertexes << "\n";
    cout << "Zbior wierzcholkow V = {";
    for (int i = 0; i < vertexes - 1; i++)
    {
        cout << i + 1 << ", ";
    }
    cout << vertexes << "}\n\n";
}

void printEdges(int** adjMatrix, int edges, int vertexes)
{
    cout << "Liczba krawedzi grafu G wynosi: " << edges << "\n";
    cout << "Zbior krawedzi V = {";

    for (int i = 0; i < vertexes; i++)
        for (int j = 0 + i; j < vertexes; j++)
        {
            if (adjMatrix[i][j])
            {
                cout << i + 1 << "-" << j + 1 << ", ";
            }
        }
    cout << "}\n\n";
}

void printAdjList(vector<int> adjList[], int V)
{
    cout << "Lista wierzcholkow grafu G:\n";
    for (int v = 0; v < V; v++)
    {
        cout << v + 1 << " -> ";
        for (auto x : adjList[v])
            cout << x + 1 << ", ";
        cout << "\n";
    }
}

void createAdjMatrixFromAdjList(int**& adjMatrix, vector<int> adjList[], int V)
{
    adjMatrix = new int* [V]();
    for (int i = 0; i < V; i++)
        adjMatrix[i] = new int[V]();

    for (int i = 0; i < V; i++)
        for (auto j : adjList[i])
            adjMatrix[i][j]++;
}

void printAdjMatrix(int** adjMatrix, int V)
{
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            std::cout << adjMatrix[i][j] << ' ';
        }
        std::cout << "\n";
    }
}

void createIncMatrixFromAdjList(int**& incMatrix, vector<int> adjList[], int V, int E)
{
    incMatrix = new int* [V]();
    for (int i = 0; i < V; i++)
        incMatrix[i] = new int[E]();

    int** adjMatrix = NULL;
    createAdjMatrixFromAdjList(adjMatrix, adjList, V);

    int edge = 0;

    for (int i = 0; i < V; i++)
        for (int j = 1 + i; j < V; j++)
        {
            if (adjMatrix[i][j])
            {
                incMatrix[i][edge] = incMatrix[j][edge] = 1;
                edge++;
            }
        }

    delete[] adjMatrix;
}

void createIncMatrixFromAdjMatrix(int**& incMatrix, int** adjMatrix, int V, int E)
{
    incMatrix = new int* [V]();
    for (int i = 0; i < V; i++)
        incMatrix[i] = new int[E]();

    int edge = 0;

    for (int i = 0; i < V; i++)
        for (int j = 0 + i; j < V; j++)
        {
            if (adjMatrix[i][j])
            {
                incMatrix[i][edge] = incMatrix[j][edge] = 1;
                edge++;
            }
        }
}

void printIncMatrix(int** adjMatrix, int V, int E)
{
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < E; j++) {
            std::cout << adjMatrix[i][j] << ' ';
        }
        std::cout << "\n";
    }
}

void printGraphRow(int V)
{
    cout << "Rzad grafu G wynosi " << V << "\n";
}

void printGraphSize(int E)
{
    cout << "Rozmiar grafu G wynosi " << E << "\n";
}

void printEdgesDeg(vector<int> adjList[], int V)
{
    cout << "Stopnie wierzcholkow:" << "\n";
    for (int v = 0; v < V; v++)
    {
        int counter = 0;
        cout << "deg(" << v + 1 << ") = ";
        for (auto x : adjList[v])
            counter++;
        cout << counter << "\n";
    }
}

void printSeriesEdgesDeg(vector<int> adjList[], int V)
{
    cout << "Ciag stopni grafu G: ";
    for (int v = 0; v < V; v++)
    {
        int counter = 0;
        for (auto x : adjList[v])
            counter++;
        cout << counter << ", ";
    }
}

bool checkIfGraphIsSimple(int** adjMatrix, int V)
{
    // Sprawdz glowna przekonta macierzy sasiedztw w poszukiwaniu petli
    for (int i = 0; i < V; i++)
            if(adjMatrix[i][i] > 0)
                return false;

    // Sprawdz pozostale krawedzie czy nie ma krawedzi wielokrotnych
    for (int i = 0; i < V - 1; i++) {
        for (int j = 1 + i; j < V; j++) {
            if (adjMatrix[i][j] > 1)
                return false;
        }
    }

    return true;
}

bool checkIfGraphIsComplete(int** adjMatrix, int V, vector<int>& supp)
{
    // Graf pelny tez jest grafem prostym
    if (!checkIfGraphIsSimple(adjMatrix, V))
        return false;

    supp.clear();

    bool flag = false;

    for (int i = 0; i < V - 1; i++) {
        for (int j = 1 + i; j < V; j++) {
            if (adjMatrix[i][j] == 0)
            {
                supp.push_back(i+1);
                supp.push_back(j+1);
                flag = true;
            }
        }
    }

    if (flag)
        return false;
    
    return true;
}