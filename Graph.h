#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include "Edge.h"
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
    void add_edge(const Vertex<T>& ver1, const Vertex<T>& ver2, int distance, int cost); //connect ver1 with ver2

    //Prints map of airports
    void print() const;

    int get_vertex_index(const Vertex<T>& ver) const; //Return the index of a given vertex (in a vector)

    void clean_visited(); //Resets if you've been to an airport or not (return to 0)

    T shortest_path(); //Finds the shortest path to the airport
    
private:
    std::vector<Vertex<T>> vertices; //list of airports 
    std::vector<std::vector<Edge>> edges; //connections
    
    

};

#endif