#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "grafy.h"

int vertexes, edges;

// Odczytaj dane z pliku i utworz z nich liste sasiedztw
void readData(std::string fileName, std::vector<int>*& adjList)
{
    std::ifstream inFile(fileName);

    if (inFile.fail()) {
        std::cout << "Problem z otworzeniem pliku";
        return;
    }

    int a, b;
    inFile >> vertexes >> edges;

    adjList = new vector<int>[vertexes];

    while (inFile >> a >> b)
    {
        addEdge(adjList, --a, --b);
    }

    return;
}

int main()
{

    int** adjMatrix = NULL;
    int** incMatrix = NULL;
    std::vector<int>* adjList = NULL;

    std::cout << "Zadanie 5\n";

    // Pobierz nazwe pliku
    std::string fileName;
    std::cout << "Podaj nazwe pliku: ";
    std::getline(std::cin, fileName);
    // Odczytaj dane z pliku i utworz z nich liste sasiedztw
    readData(fileName, adjList);

    // Utworz macierz sasiedztwa z listy sasiedztwa
    createAdjMatrixFromAdjList(adjMatrix, adjList, vertexes);

    // Utworz macierz sasiedztwa z macierzy sasiedztwa
    createIncMatrixFromAdjMatrix(incMatrix, adjMatrix, vertexes, edges);

    printAdjList(adjList, vertexes);

    // Zwolnij pamiec
    delete[] adjMatrix;
    adjMatrix = NULL;

    delete[] incMatrix;
    adjMatrix = NULL;

    delete[] adjList;
    adjList = NULL;

}