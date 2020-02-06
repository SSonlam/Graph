/**
 * Edge is the simplest structure of the graph
 * All edges are directed
 * Each edge belongs to a vertex
 */
#ifndef EDGE_H
#define EDGE_H

 // forward declaration for class Vertex
class Vertex;

class Edge {
    friend class Vertex;
    friend class Graph;

private:
    Vertex* Finish;
    int EdgeWeight;
    /** constructor with label and weight */
    Edge(Vertex *To, int Weight);

};

#endif
