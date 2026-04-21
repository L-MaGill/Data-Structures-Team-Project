#include <iostream>
#include <cstdio>
#include <vector>

#include "Graph.h"
#include "MinHeap.h"

#define INT_MAX 1000

using namespace std;

template <typename T>
void someVectorFunction () {
    vector<T> someVector;
    
}

    //Add an airport
    template <typename T>
    void Graph<T>::insert_vertex(const Vertex<T>& ver) {

        if (get_vertex_index(ver) == -1) {
            vertices.push_back(ver); //insert the vertex to the array of vertices
            std::vector<Edge> tmp;
            edges.push_back(tmp); //insert empty vector to the edges
        }

    }

    //Add an edge
    //connect ver1 with ver2
    template <typename T>
    void Graph<T>::add_edge(const Vertex<T>& ver1, const Vertex<T>& ver2, int distance, int cost) {

        int i1 = get_vertex_index(ver1);
        int i2 = get_vertex_index(ver2);

        if (i1 == -1 || i2 == -1) {
            throw std::string("Add_edge: incorrect vertices");
        }

        Edge v(i1, i2, distance, cost);
        edges[i1].push_back(v);

    }

    //Prints map of airports
    template <typename T>
    void Graph<T>::print() const {
        for (int i = 0; i < vertices.size(); i++) {
            cout << "{ " << vertices[i].getData() << ": ";

            for(int j = 0; j < edges[i].size(); j++) {
                cout << '{' << vertices[edges[i][j].dest].getData() << ", ";
                cout << edges[i][j].dist << ", " << edges[i][j].cost << " } ";
            }

            std::cout << " }\n";
        }
    }

    template <typename T>
    int Graph<T>::get_vertex_index(const Vertex<T>& ver) const {
        for(int i = 0; i < vertices.size(); i++) {

            if (vertices[i].getData() == ver.getData()) {
                return i;
            }

        }

        return -1;
}

    template <typename T>
    void Graph<T>::clean_visited() {
        for(Vertex<T>& v : vertices) {
            v.setVisited(false);
        }
    }



    template <typename T>
    T shortest_path()





