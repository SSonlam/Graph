/**
 * Edge is the simplest structure of the graph
 * All edges are directed
 * Each edge belongs to a vertex
 */

#include "edge.h"

Edge::Edge(Vertex *To, int Weight) {
    Finish = To;
    EdgeWeight = Weight;
}
