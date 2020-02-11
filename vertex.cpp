/**
 * A Graph is made up of Vertex objects that hold data values
 * A vertex is connected to other vertices via Edges
 * A vertex can be visited/unvisited
 * Can connect to another vertex via directed edge with weight
 * The edge can be disconnected
 * A vertex cannot have an edge back to itself
 * getNextNeighbor returns the next neighbor each time it is called
 * when there are no more neighbors, the vertex label is returned
 */

#include "vertex.h"
#include "edge.h"
#include <algorithm>

using namespace std;

ostream &operator<<(ostream &Os, const Vertex &V) {
    Os << V.VertexName;
    return Os;
}
Vertex::Vertex(const string &Label) {
    VertexName = Label;
}
string Vertex::getVertexName() {
    return VertexName;
}

void Vertex::selectionSort() {
    int I, J, Min;
    Vertex* Temp;
    for (I = 0; I < Neighbors.size(); I++) {
        Min = I;
        for (J = I + 1; J < Neighbors.size(); J++) {
            if (Neighbors[J]->VertexName < Neighbors[Min]->VertexName)
                Min = J;
            Temp = Neighbors[I];
            Neighbors[I] = Neighbors[Min];
            Neighbors[Min] = Temp;
        }
    }
}

Vertex::~Vertex(){}
