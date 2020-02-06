#include "graph.h"
#include <algorithm>
#include <cassert>
#include <map>
#include <utility>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

Graph::Graph(bool DirectionalEdges) {
    for (int i = 0; i < AlphabetSize; i++) {
        for (int j = 0; j < AlphabetSize; j++) {
            AdjMatrix[i][j] = -1;
        }
    }
}

Graph::~Graph() {
    for (int i = 0; i < VertexVector.size(); i++) {
        delete VertexVector[i];
    }
}

bool Graph::readFile(const string &Filename) {
    ifstream inFile;
    inFile.open(Filename);
    if (!inFile) {
        cout << "Failure opening file";
    }
    int x;
    inFile >> x;
    string first, second;
    int third;
    for (int i = 0; i < x; i++) {
        inFile >> first >> second >> third;
        add(first);
        add(second);
        connect(first, second, third);
    }

    inFile.close();


    return true; 

}

int Graph::verticesSize() const { 
    return numberOfVertices; 
}

int Graph::edgesSize() const { 
    int count = 0;
    for (int i = 0; i < AlphabetSize; i++) {
        for (int j = 0; j < AlphabetSize; j++) {
            if (AdjMatrix[i][j] > -1) {
                count++;
            }
        }
    }
    return count;
}

int Graph::neighborsSize(const string &Label) { 
    if (VertexMap[Label] == nullptr) {
        return -1;
    }
    return VertexMap[Label]->Neighbors.size();
}

bool Graph::add(const string &Label) {
    if (contains(Label)) {
        return false;
    }
        Vertex* AddedVertex = new Vertex(Label);
        VertexMap[Label] = AddedVertex;
        VertexVector.push_back(AddedVertex);
     /*   if (Head == nullptr) {
            Head = AddedVertex;
        }
        */
        numberOfVertices++;
        return true;
}

/** return true if vertex already in graph */
bool Graph::contains(const string &Label) {
    if(VertexMap[Label] == nullptr){
        return false;
    }
    return true;

}

string Graph::getEdgesAsString(const string &Label) { 
    if (VertexMap[Label]->Neighbors.empty()) {
        return "";
    }
    string EdgeAsString;
    for (int i = 0; i < VertexMap[Label]->Neighbors.size(); i++) {
      //  Vertex* Temp = VertexMap[Label]->Neighbors[i];
        int Number = AdjMatrix[getAlphabetInt(Label)][getAlphabetInt(VertexMap[Label]->Neighbors[i])];

        //getting our edge to convert to string
        string IntToString;
        stringstream SS;
        SS << Number;
        IntToString = SS.str();

        EdgeAsString += VertexMap[Label]->Neighbors[i] + "(" + IntToString + ")";
        if (i != VertexMap[Label]->Neighbors.size() - 1) {
            EdgeAsString += ",";
        }
    }
    return EdgeAsString; 
}

bool Graph::connect(const string &From, const string &To, int Weight) {
    if (VertexMap[From] == VertexMap[To]) {
        return false;
    }
    else if (VertexMap[From] == nullptr || VertexMap[To] == nullptr) {
        return false;
    }
    if (AdjMatrix[getAlphabetInt(From)][getAlphabetInt(To)] == -1) {
        Edge EdgeConnect(VertexMap[To], Weight);
       // EdgeVector.push_back(&EdgeConnect);
        VertexMap[From]->Neighbors.push_back(To);
        sort(VertexMap[From]->Neighbors.begin(), VertexMap[From]->Neighbors.end());

        AdjMatrix[getAlphabetInt(From)][getAlphabetInt(To)] = Weight;
        return true;
    }
    return false;
}
bool Graph::disconnect(const string &From, const string &To) { 
    if (AdjMatrix[getAlphabetInt(From)][getAlphabetInt(To)] == -1) {
        return false;
    }
    AdjMatrix[getAlphabetInt(From)][getAlphabetInt(To)] = -1;
    /*
    for (int i = 0; i < EdgeVector.size(); i++) {
        if (EdgeVector[i]->Finish->VertexName == To) {
            EdgeVector.erase(EdgeVector.begin() + i);
        }
    }
    */
    for (int i = 0; i < VertexMap[From]->Neighbors.size(); i++) {
        if (To == VertexMap[From]->Neighbors[i]) {
            VertexMap[From]->Neighbors.erase(VertexMap[From]->Neighbors.begin() + i);
        }
    }
    return true; 
}

int Graph::getAlphabetInt(const string Target) {
    for (int i = 0; i < AlphabetSize; i++) {
        if (Target == Alphabet[i]) {
            return i;
        }
    }
    for (int i = 0; i < AlphabetSize; i++) {
        if (Target == AlphabetLowerCase[i]) {
            return i;
        }
    }
    return -1;
}

void Graph::dfs(const string &StartLabel, void Visit(const string &Label)) {}

void Graph::bfs(const string &StartLabel, void Visit(const string &Label)) {}

// store the weights in a map
// store the previous label in a map
pair<map<string, int>, map<string, string>>
Graph::dijkstra(const string &StartLabel) const {
    map<string, int> Weights;
    map<string, string> Previous;
    return make_pair(Weights, Previous);
}

/**
 * minimum spanning tree
 * @param function to be called on each edge
 * @return length of the minimum spanning tree or -1 if start vertex not found
 */
int Graph::mst(const string &StartLabel,
    void Visit(const string &From, const string &To,
        int Weight)) const {
    assert(!DirectionalEdges);
    return 0;
}
