#include "graph.h"
#include <algorithm>
#include <cassert>
#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>


using namespace std;

Graph::Graph(bool DirectionalEdges) {
    //Adjacency matrix for edges
    this->DirectionalEdges = DirectionalEdges;
    for (int I = 0; I < ALPHABETSIZE; I++) {
        for (int J = 0; J < ALPHABETSIZE; J++) {
            AdjMatrix[I][J] = -1;
        }
    }
}

//destructor
Graph::~Graph() {
    for (int I = 0; I < VertexVector.size(); I++) {
        delete VertexVector[I];
    }
    for (int I = 0; I < EdgeVector.size(); I++) {
        delete EdgeVector[I];
    }
}

//read in file with expected formatting
bool Graph::readFile(const string &Filename) {
    ifstream InFile;
    InFile.open(Filename);
    if (!InFile) {
        cout << "Failure opening file";
    }
    int X;
    InFile >> X;
    string First, Second;
    int Third;
    for (int I = 0; I < X; I++) {
        InFile >> First >> Second >> Third;
        add(First);
        add(Second);
        connect(First, Second, Third);
        if (this->DirectionalEdges == false) {
            connect(Second, First, Third);
        }
    }

    InFile.close();
    return true;

}

//total vertices in graph
int Graph::verticesSize() const {
    return NumberOfVertices;
}

//returns # of edges in the matrix
int Graph::edgesSize() const {
    int Count = 0;
    for (int I = 0; I < ALPHABETSIZE; I++) {
        for (int J = 0; J < ALPHABETSIZE; J++) {
            if (AdjMatrix[I][J] > -1) {
                Count++;
            }
        }
    }
    return Count;
}

//# of neighbors a vertex has
int Graph::neighborsSize(const string &Label) {
    if (VertexMap[Label] == nullptr) {
        return -1;
    }
    return VertexMap[Label]->Neighbors.size();
}

//adds new Vertex and adds to map to keep track of it
//also adds to Vertex vector
bool Graph::add(const string &Label) {
    if (contains(Label)) {
        return false;
    }
    auto AddedVertex = new Vertex(Label);
    VertexMap[Label] = AddedVertex;
    VertexVector.push_back(AddedVertex);
    //increment # of vertices
    NumberOfVertices++;
    return true;
}

/** return true if vertex already in graph */
bool Graph::contains(const string &Label) {
    if (VertexMap[Label] == nullptr) {
        return false;
    }
    return true;

}

//returns all the neighbors of called vertex, with edge weight
string Graph::getEdgesAsString(const string &Label) {
    //has no neighbors
    if (VertexMap[Label]->Neighbors.empty()) {
        return "";
    }
    string EdgeAsString;
    for (int I = 0; I < VertexMap[Label]->Neighbors.size(); I++) {
        int Number = AdjMatrix[getAlphabetInt(Label)]
            [getAlphabetInt(VertexMap[Label]->Neighbors[I]->VertexName)];

        //getting our edge to convert to string
        string IntToString;
        stringstream SS;
        SS << Number;
        IntToString = SS.str();

        EdgeAsString += VertexMap[Label]->Neighbors[I]->VertexName +
            "(" + IntToString + ")";
        if (I != VertexMap[Label]->Neighbors.size() - 1) {
            EdgeAsString += ",";
        }
    }
    return EdgeAsString;
}

//connecting adds a Weight to adj matrix, creates edge, adds to
//vertex neighbors as well
bool Graph::connect(const string &From, const string &To, int Weight) {
    //self loop check
    if (VertexMap[From] == VertexMap[To]) {
        return false;
    }
    //connection to empty vertex
    if (VertexMap[From] == nullptr || VertexMap[To] == nullptr) {
        return false;
    }

    if (AdjMatrix[getAlphabetInt(From)][getAlphabetInt(To)] == -1) {
        VertexMap[From]->Neighbors.push_back(VertexMap[To]);
        VertexMap[From]->selectionSort();
        AdjMatrix[getAlphabetInt(From)][getAlphabetInt(To)] = Weight;
        Edge* EdgeAdded = new Edge(VertexMap[To], Weight);
        EdgeVector.push_back(EdgeAdded);
        return true;
    }
    return false;
}

//disconnect sets adj matrix edge back to -1
bool Graph::disconnect(const string &From, const string &To) {
    if (AdjMatrix[getAlphabetInt(From)][getAlphabetInt(To)] == -1) {
        return false;
    }
    AdjMatrix[getAlphabetInt(From)][getAlphabetInt(To)] = -1;
    //also take away from Vertex neighbor vector
    for (int I = 0; I < VertexMap[From]->Neighbors.size(); I++) {
        if (VertexMap[To] == VertexMap[From]->Neighbors[I]) {
            VertexMap[From]->Neighbors.erase(VertexMap[From]->Neighbors.begin() + I);
        }
    }

    //undirected graph will disconnect both edges
    if (this->DirectionalEdges == false) {
        AdjMatrix[getAlphabetInt(To)][getAlphabetInt(From)] = -1;
        for (int I = 0; I < VertexMap[To]->Neighbors.size(); I++) {
            if (VertexMap[From] == VertexMap[To]->Neighbors[I]) {
                VertexMap[To]->Neighbors.erase(VertexMap[To]->Neighbors.begin() + I);
            }
        }
    }
    return true;
}

//matches string with int for adj matrix
int Graph::getAlphabetInt(const string Target) {
    for (int I = 0; I < ALPHABETSIZE; I++) {
        if (Target == Alphabet[I]) {
            return I;
        }
    }
    for (int I = 0; I < ALPHABETSIZE; I++) {
        if (Target == AlphabetLowerCase[I]) {
            return I;
        }
    }
    return -1;
}

void Graph::dfs(const string &StartLabel, void Visit(const string &Label)) {
    if (VertexMap[StartLabel] == nullptr) {
        return;
    }
    stack<Vertex*> Stack;
    visitedToFalse();
    Stack.push(VertexMap[StartLabel]);
    Visit(StartLabel);
    VertexMap[StartLabel]->IsVisited = true;

    while (!Stack.empty()) {
        Vertex* Temp = Stack.top();
        bool VisitCheck = true;
        for (int I = 0; I < Temp->Neighbors.size(); I++) {
            if (Temp->Neighbors[I]->IsVisited == false) {
                VisitCheck = false;
            }
        }
        if (VisitCheck) {
            Stack.pop();
        }
        else {
            for (int I = 0; I < Temp->Neighbors.size(); I++) {
                if (Temp->Neighbors[I]->IsVisited == false) {
                    Stack.push(Temp->Neighbors[I]);
                    Visit(Temp->Neighbors[I]->VertexName);
                    Temp->Neighbors[I]->IsVisited = true;
                    break;
                }
            }
        }
    }
}

void Graph::bfs(const string &StartLabel, void Visit(const string &Label)) {
    if (VertexMap[StartLabel] == nullptr) {
        return;
    }
    visitedToFalse();
    queue<Vertex*> Queue;
    Queue.push(VertexMap[StartLabel]);
    Visit(StartLabel);
    VertexMap[StartLabel]->IsVisited = true;
    while (!Queue.empty()) {

        Vertex* Temp = Queue.front();
        Queue.pop();
        for (int I = 0; I < Temp->Neighbors.size(); I++) {
            if (Temp->Neighbors[I]->IsVisited == false) {
                Queue.push(Temp->Neighbors[I]);
                Visit(Temp->Neighbors[I]->VertexName);
                Temp->Neighbors[I]->IsVisited = true;
            }
        }
    }
}

void Graph::visitedToFalse() {
    for (int I = 0; I < VertexVector.size(); I++) {
        VertexVector[I]->IsVisited = false;
    }
}
int Graph::minDistance(int Distance[], bool SptSet[])
{
    // Initialize min value 
    int Minimum = INT_MAX;
    int MinIndex;

    for (int V = 0; V < ALPHABETSIZE; V++) {
        if (SptSet[V] == false && Distance[V] <= Minimum) {
            Minimum = Distance[V], MinIndex = V;
        }
    }

    return MinIndex;
}

int Graph::minDistance2(int Distance[], bool SptSet[])
{
    // Initialize min value 
    int Minimum = INT_MAX;
    int MinIndex;

    for (int V = 0; V < ALPHABETSIZE; V++) {
        if (SptSet[V] == false && Distance[V] < Minimum) {
            Minimum = Distance[V], MinIndex = V;
        }
    }

    return MinIndex;
}

// Function that implements Dijkstra's single source shortest path 
// algorithm for a graph represented using adjacency matrix 
// representation 
pair<map<string, int>, map<string, string>>
Graph::dijkstra(const string &StartLabel)
{
    map<string, int> Weights;
    map<string, string> Previous;
    int Distance[ALPHABETSIZE]; // The output array.  dist[i] will hold the shortest 
    // distance from src to i 

    bool SptSet[ALPHABETSIZE]; // sptSet[i] will be true if vertex i is included in shortest 
    // path tree or shortest distance from src to i is finalized 

    // Initialize all distances as INFINITE and stpSet[] as false 
    for (int I = 0; I < ALPHABETSIZE; I++) {
        Distance[I] = INT_MAX, SptSet[I] = false;
    }

    // Distance of source vertex from itself is always 0 
    Distance[getAlphabetInt(StartLabel)] = 0;

    // Find shortest path for all vertices 
    for (int Count = 0; Count < ALPHABETSIZE - 1; Count++) {
        // Pick the minimum distance vertex from the set of vertices not 
        // yet processed. u is always equal to src in the first iteration. 
        int U = minDistance(Distance, SptSet);

        // Mark the picked vertex as processed 
        SptSet[U] = true;

        // Update dist value of the adjacent vertices of the picked vertex. 
        for (int V = 0; V < ALPHABETSIZE; V++) {

            // Update dist[v] only if is not in sptSet, there is an edge from 
            // u to v, and total weight of path from src to  v through u is 
            // smaller than current value of dist[v] 
            if (!SptSet[V] && AdjMatrix[U][V] && Distance[U] != INT_MAX
                && AdjMatrix[U][V] != -1 && Distance[U] + AdjMatrix[U][V] < Distance[V]) {
                Distance[V] = Distance[U] + AdjMatrix[U][V];
                Weights[Alphabet[V]] = Distance[V];
                Previous[Alphabet[V]] = Alphabet[U];
            }
        }
    }
    return make_pair(Weights, Previous);
}

void Graph::selectionSortVertex() {
    int I, J, Min;
    Vertex* Temp;
    for (I = 0; I < VertexVector.size(); I++) {
        Min = I;
        for (J = I + 1; J < VertexVector.size(); J++) {
            if (VertexVector[J]->VertexName < VertexVector[Min]->VertexName)
                Min = J;
            Temp = VertexVector[I];
            VertexVector[I] = VertexVector[Min];
            VertexVector[Min] = Temp;
        }
    }
}

void Graph::selectionSortEdge() {
    int I, J, Min;
    Edge* Temp;
    for (I = 0; I < EdgeVector.size(); I++) {
        Min = I;
        for (J = I + 1; J < EdgeVector.size(); J++) {
            if (EdgeVector[J]->Finish->VertexName < EdgeVector[Min]->Finish->VertexName) {
                Min = J;
            }
            Temp = EdgeVector[I];
            EdgeVector[I] = EdgeVector[Min];
            EdgeVector[Min] = Temp;
        }
    }
}
/*
void Graph::primMST() {
    map<Vertex*, Vertex*> A;
    map<Vertex*, Vertex*> PARENT;
    map<Vertex*, int> KEY;
    selectionSortVertex();
    selectionSortEdge();

    for (auto c : VertexVector) {
        PARENT[c] = '\0';
        KEY[c] = INT_MAX;
    }
    KEY[VertexMap["A"]] = 0;
    vector<Vertex*> Q = VertexVector;


    while (!Q.empty()) {
        Vertex* u = Q.front();
        vector<Vertex*>::iterator itr = remove(Q.begin(), Q.end(), u);
        Q.erase(itr, Q.end());
        if (PARENT[u] != '\0') {
            A[u] = PARENT[u];
        }
        vector <pair<string, Edge*> > adj;
        adj.push_back(make_pair(u->VertexName, EdgeVector.front()));
        for (pair<string, Edge*> v : adj) {
            cout << v.second->Finish->VertexName << endl;
            if (find(Q.begin(), Q.end(), VertexMap[v.first]) != Q.end()) {
                if (v.second->EdgeWeight < KEY[VertexMap[v.first]]) {
                    PARENT[VertexMap[v.first]] = u;
                    KEY[VertexMap[v.first]] = v.second->EdgeWeight;
                }

            }
        }
        
    }
    
}
*/
