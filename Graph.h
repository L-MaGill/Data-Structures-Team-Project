#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include "Vertex.h"
#include "Edge.h"
#include <vector>
#include <iostream>
using namespace std;


template <typename T>
class Graph {
public:
    //Create a graph
    Graph() {}

    //Add an airport
    void insert_vertex(const Vertex<T>& ver, const string & city);

    //Add an edge
    void add_edge(const Vertex<T>& ver1, const Vertex<T>& ver2, int distance, int cost); //connect ver1 with ver2

    //Prints map of airports
    void print() const;

    int get_vertex_index(const Vertex<T>& ver); //Return the index of a given vertex (in a vector)

    void clean_visited(); //Resets if you've been to an airport or not (return to 0)

    int getAirportIndex(const string& airportCode) const; //Finds the index of the desired airport in the vector

    string getState(const string& city) const; //Finds the state

    int getAirportData (const string& fileLine);

    void shortest_path_to_state (const T& src, const string& destState);


    void shortest_path(const T& src, const T& dest);//Finds the shortest path to the airport
    void shortest_pathStops(const T& src, const T& dest); 
private:
    std::vector<Vertex<T>> vertices; //list of airports 
    std::vector<std::vector<Edge>> edges; //connections
    vector<string> airportCities; //Stores the city for each vertex
    
    

};

#endif