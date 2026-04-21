#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include "Edge.h"
#include "Graph.cpp"
#include <vector>
#include <string>
#include <iostream>


template <typename T>
class Graph {
public:
    //Create a graph
    Graph() {}

    //Add an airport
    void insert_vertex(const Vertex<T>& ver);

    //Add an edge
    void add_edge(const Vertex<T>& ver1, const Vertex<T>& ver2, int weight); //connect ver1 with ver2

    //Prints map of airports
    void print() const;

private:
    std::vector<Vertex<T>> vertices; //list of airports 
    std::vector<std::vector<Edge>> edges; //connections
    
    int get_vertex_index(const Vertex<T>& ver); //Return the index of a given vertex (in a vector)

    void clean_visited(); //Resets if you've been to an airport or not (return to 0)

};

#endif