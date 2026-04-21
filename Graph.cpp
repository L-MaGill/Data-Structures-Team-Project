#include <iostream>
#include <cstdio>
#include <vector>

#include "Graph.h"
#include "MinHeap.h"
#include "Vertex.h"
#include "Edge.h"

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


    /*
    template <typename T>
    T shortest_path(const Vertex<T>& src, const Vertex<T>& dest, int distance, int cost){
        
        //indexes
        int initial_src = get_vertex_index(src);
        int initial_dest = get_vertex_index(dest);

        int weight = distance + cost;

        //clears visited
        clean_visited();

        if (initial_src == -1 || initial_dest == -1) {
            throw std::string("Shortest path: incorrect vertices"); 
        }

        MinHeap<> pq;



        clean_visited();

        return distances[initial_dest];


    }

    */


    template <typename T>
    int Graph<T>::getAirportIndex(const string& airportCode) const{
        for (int i = 0 ; i < vertices.size(); i++) {
            if(vertices[i].getData() == airportCode) 
            //Loops through the vertex to find the requested code    
            return i;     
        }
        //returns -1 if the code is never found
        return -1;
    }

    template <typename T>
    string Graph<T>::getState(const string& city) const { 
        int commaPosition = city.find(',');
        string state = city.substr(commaPosition + 2);
        return state;
        
    }

    /*
    vector<string> getAirportData (const string& fileLine) {
        vector<string> airportAttributes; //Makes a vector of all of the 6 attributes of each flight
        int start = 0; //start at the first attribute (0)

        //Iterate over the list to find the commas seperating the attributes
        while (start < line.size()) {
            //Have to account for when there are quotations around an attribute (comma could mess it up)
                if(fileLine[start] = '"') {
                    int endQuote = line.find('"', start + 1); //Find the index of the end of the quote
                    string currAttribute = line.substr(start+1, endQuote - start - 1); //Isolate the data
                    airportAttributes.push_back(currAttribute); //Add it to attribute list
                    start = endQuote + 1; //Update starting position
                }
       

            else {
                int commaPosition = line.find(',', start); //Find the first comma
                string currAttribute = line.substr(start, commaPosition - start); //Seperate the data before the comma
                airportAttributes.push_back(currAttribute); //Add it to attributes list
                start = commaPosition + 1; //Update starting position
            }

            if (start < line.size() && line[start] == ',') { //If you start on a comma, go to the next attribute
                start++;
            }
        }

    return airportAttributes;
            
    }

*/

