/**
 * A graph is made up of vertices and edges.
 * Vertex labels are unique.
 * A vertex can be connected to other vertices via weighted, directed edge.
 * A vertex cannot connect to itself or have multiple edges to the same vertex
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "edge.h"
#include "vertex.h"
#include <map>
#include <string>
#include <vector>

using namespace std;
    const int ALPHABETSIZE = 26;

class Graph {
   // const int AlphabetSize = 26;
public:
    // constructor, empty graph
    explicit Graph(bool DirectionalEdges = true);

    /** destructor, delete all vertices and edges */
    ~Graph();

    // @return true if vertex added, false if it already is in the graph
    bool add(const string &Label);

    // @return true if vertex is in the graph
    bool contains(const string &Label);

    // @return total number of vertices
    int verticesSize() const;
        
    // Add an edge between two vertices, create new vertices if necessary
    // A vertex cannot connect to itself, cannot have P->P
    // For digraphs (directed graphs), only one directed edge allowed, P->Q
    // Undirected graphs must have P->Q and Q->P with same weight
    // @return true if successfully connected
    bool connect(const string &From, const string &To, int Weight = 0);

    // Remove edge from graph
    // @return true if edge successfully deleted
    bool disconnect(const string &From, const string &To);

    // @return total number of edges
    int edgesSize() const;

    int getAlphabetInt(const string Target);

    // @return number of edges from given vertex, -1 if vertex not found
    int neighborsSize(const string &Label);

    // @return string representing edges and weights, "" if vertex not found
    // A-3->B, A-5->C should return B(3),C(5)
    string getEdgesAsString(const string &Label);

    // Read edges from file
    // first line of file is an integer, indicating number of edges
    // each line represents an edge in the form of "string string int"
    // vertex labels cannot contain spaces
    // @return true if file successfully read
    bool readFile(const string &Filename);

    // depth-first traversal starting from given startLabel
    void dfs(const string &StartLabel, void Visit(const string &Label));

    void visitedToFalse();

    // breadth-first traversal starting from startLabel
    // call the function visit on each vertex label */
    void bfs(const string &StartLabel, void Visit(const string &Label));
    int minDistance(int Dist[], bool SptSet[]);
    int minDistance2(int Distance[], bool SptSet[]);
    // dijkstra's algorithm to find shortest distance to all other vertices
    // and the path to all other vertices
    // Path cost is recorded in the map passed in, e.g. weight["F"] = 10
    // How to get to the vertex is recorded previous["F"] = "C"
    // @return a pair made up of two map objects, Weights and Previous
    pair<map<string, int>, map<string, string>>
        dijkstra(const string &StartLabel);
        
    // minimum spanning tree
    // ONLY works for NONDIRECTED graphs
    // ASSUMES the edge [P->Q] has the same weight as [Q->P]
    // @return length of the minimum spanning tree or -1 if start vertex not
    void primMST();
    void printMST(int parent[]);
  //  void primMST(const string &StartLabel);
    void selectionSortVertex();
    void selectionSortEdge();
   // bool createsMST(const string &StartLabel, void Visit(const string &From, const string &To,
     //   int Weight));
    void printMinSpanningTree();
    /*
    int mst(const string &StartLabel,
        void Visit(const string &From, const string &To, int Weight)) const;
        */
    bool getDirectional() {
        return DirectionalEdges;

    }
private:
    // default is directional edges is true,
    // can only be modified when graph is initially created
    // when set to false,
    // create 2 edges, one from P->Q and another from Q->P with same weight
    bool DirectionalEdges;
    map<string, Vertex*> VertexMap;
    int NumberOfVertices = 0;
    int AdjMatrix[ALPHABETSIZE][ALPHABETSIZE];
    vector<Vertex*>VertexVector;
    vector<Edge*> EdgeVector;
    vector<string> Alphabet = { "A","B","C","D","E","F","G","H","I","J","K",
        "L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };
    vector<string> AlphabetLowerCase = { "a","b","c","d","e","f","g","h","i","j","k",
        "l","m","n","o","p","q","r","s","t","u","v","w","x","y","z" };
    // add additional variables and functions as needed
};

#endif // GRAPH_H