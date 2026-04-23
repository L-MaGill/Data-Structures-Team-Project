#include <iostream>
#include <cstdio>
#include <vector>

#include "Graph.h"
#include "MinHeap.h"
#include "Vertex.h"
#include "Edge.h"

#define INT_MAX 1000000000000000

using namespace std;


    //Add an airport
    template <typename T>
    void Graph<T>::insert_vertex(const Vertex<T>& ver, const string & city) {

        if (get_vertex_index(ver) == -1) {
            vertices.push_back(ver); //insert the vertex to the array of vertices
            airportCities.push_back(city);
            std::vector<Edge> tmp;
            edges.push_back(tmp); //insert empty vector to the edges
        }

    }

    //////////////////////////////////////////////////////////////////////////////////////////////////

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
    
    template <typename T>
    void add_undirected_edge(const Vertex<T>& ver1, const Vertex<T>& ver2, int cost){

        add_edge(ver1, ver2, 0, cost);
        add_edge(ver2, ver1, 0, cost);


    }

    //////////////////////////////////////////////////////////////////////////////////////////////////

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

    //////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T>
    int Graph<T>::get_vertex_index(const Vertex<T>& ver)  {
        for(int i = 0; i < vertices.size(); i++) {

            if (vertices[i].getData() == ver.getData()) {
                return i;
            }

        }

        return -1;
    }

//////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T>
    void Graph<T>::clean_visited() {
        for(Vertex<T>& v : vertices) {
            v.setVisited(false);
        }
    }
    

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
    

    template <typename T>
    void Graph<T>::shortest_path(const T& src, const T& dest){
        
        //Count how many vertices we have
        int n = vertices.size();
        if (n == 0) {
            cout << "No flights found :(";
            return;
        }

        //assign the current and adjacent verticies
        int curr = getAirportIndex(src);
        int adj = getAirportIndex(dest);

        
        vector<long> minDistance (n, INT_MAX);
        vector<long> totalCost (n, INT_MAX);
        vector<int> previous (n, -1); 
        vector<bool> visited(n, false);

        minDistance[curr] = 0;
        totalCost[curr] = 0;

        
        for (int i = 0 ; i < n; i++) {
            //create curr it travel around the graph
            // minPath is for finding the minimum distance between edges and travling there
            int next = -1;
            long minPath = INT_MAX;

            for (int j = 0; j < n; j++) {

                //checks if the minimum Cost is less than the path minimum
                if(!visited[j] && minDistance[j] < minPath) {
                    minPath = minDistance[j];
                    next = j;
                }
            }

            //If we haven't moved, there is no path
            if (next == -1) break;
            visited[next] = true;
            
            
            // Assigning the new distance and location
            for (Edge& edgy : edges[next]) {
                int goingTo = edgy.dest;
                long newDist = minDistance[next] + edgy.dist;
                long newCost = totalCost[next] + edgy.cost; 
                
                //Checks if the new path is shorter than the previously min path and updates accordingly
                if (newDist < minDistance[goingTo]) {
                    minDistance[goingTo] = newDist;
                    totalCost[goingTo] = newCost;
                    previous[goingTo] = next;
                }
            }
        } 
        
        //Checks if the path to the destination exists
        if (minDistance[adj] == INT_MAX) {
            cout << "Shortest route from " << src << " to " << dest << ": None" << endl;
            return;
        }
        
        
        // Reverses the path
        vector<int> path;
        for (int i = adj; i != -1; i = previous[i]) {
            path.push_back(i);
        }

        // Undo the reverse?? 
        vector<int> forwardPath;
        for (int i = path.size() - 1; i >= 0; i--) {
            forwardPath.push_back(path[i]);
        }
        path = forwardPath;

        if (path.empty() || path[0] != curr) {
            cout << "Shortest route from" << src << " to " << dest << ": None" << endl;
            return;
        }
        
        cout << "Shortest route from  " << src << " to " << dest << ": ";
        for (int i = 0; i < path.size(); i++) {
            cout << vertices[path[i]].getData();
            if (i + 1 < path.size()) 
                cout << " -> ";
        }

        cout << ". The length is " << minDistance[adj] << ". The cost is " << totalCost[adj] << ".\n";
    }

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
  


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

    template <typename T>
    void Graph<T>::shortest_path_to_state (const T& src, const string& destState) {
        
        int n = vertices.size();
        if (n == 0) {
            cout << "No flights found :(";
            return;
        }



        int curr = getAirportIndex(src);
        //int adj = getAirportIndex(dest);
        vector<long> minDistance (n, INT_MAX);
        vector<long> totalCost (n, INT_MAX);
        vector<int> previous (n, -1); 
        vector<bool> visited(n, false);

        minDistance[curr] = 0;
        totalCost[curr] = 0;

        for (int i = 0 ; i < n; i++) {
            //create curr it travel around the graph
            // minPath is for finding the minimum distance between edges and travling there
            int next = -1;
            long minPath = INT_MAX;

            for (int j = 0; j < n; j++) {

                //checks if the minimum Cost is less than the path minimum
                if(!visited[j] && minDistance[j] < minPath) {
                    minPath = minDistance[j];
                    next = j;
                }
            }

            //If we haven't moved, there is no path
            if (next == -1) break;
            visited[next] = true;
            
            
            // Assigning the new distance and location
            for (Edge& edgy : edges[next]) {
                int goingTo = edgy.dest;
                long newDist = minDistance[next] + edgy.dist;
                long newCost = totalCost[next] + edgy.cost; 
                
                //Checks if the new path is shorter than the previously min path and updates accordingly
                if (newDist < minDistance[goingTo]) {
                    minDistance[goingTo] = newDist;
                    totalCost[goingTo] = newCost;
                    previous[goingTo] = next;
                }
            }
        } 

        bool statePath = 0;
        cout << "Shortest paths from " << src << " to " <<  destState << " state airports are: " << endl;

        cout << "Path               Length      Cost" << endl;
        for (int i = 0; i < n; i++) {
            if (minDistance[i] == INT_MAX) 
                continue;
            string city = airportCities[i];
            if (getState(city) != destState) //Make sure that they're in the same state
              continue;
            
              statePath = 1;

              // Reverses the path
            vector<int> path;
            for (int j = i; j != -1; j = previous[j]) {
                path.push_back(j);
            }

            // Undo the reverse?? 
            vector<int> forwardPath;
            for (int k = path.size() - 1; k >= 0; k--) {
                forwardPath.push_back(path[k]);
            }
            path = forwardPath;

            if (path.empty() || path[0] != curr) {
                continue;
            }
    
            cout << src ;
                for (int k = 1; k < path.size(); k++) {
                    cout << "->" << vertices[path[k]].getData();
                }
                cout << "               " << minDistance[i] << "      " << totalCost[i] << endl;
                
            }
              
        
        if (!statePath)
            cout << "No paths exist to any airports in " << destState << " state" << endl;
    }
    






//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
    

    template <typename T>
    void Graph<T>::shortest_pathStops(const T& src, const T& dest){
        
        //Count how many vertices we have
        int n = vertices.size();
        if (n == 0) {
            cout << "No flights found :(";
            return;
        }

        //assign the current and adjacent verticies
        int curr = getAirportIndex(src);
        int adj = getAirportIndex(dest);

        
        vector<long> minDistance (n, INT_MAX);
        vector<long> totalCost (n, INT_MAX);
        vector<int> previous (n, -1); 
        vector<bool> visited(n, false);

        minDistance[curr] = 0;
        totalCost[curr] = 0;

        
        for (int i = 0 ; i < n; i++) {
            //create curr it travel around the graph
            // minPath is for finding the minimum distance between edges and travling there
            int next = -1;
            long minPath = INT_MAX;

            for (int j = 0; j < n; j++) {

                //checks if the minimum Cost is less than the path minimum
                if(!visited[j] && minDistance[j] < minPath) {
                    minPath = minDistance[j];
                    next = j;
                }
            }

            //If we haven't moved, there is no path
            if (next == -1) break;
            visited[next] = true;
            
            
            // Assigning the new distance and location
            for (Edge& edgy : edges[next]) {
                int goingTo = edgy.dest;
                long newDist = minDistance[next] + edgy.dist;
                long newCost = totalCost[next] + edgy.cost; 
                
                //Checks if the new path is shorter than the previously min path and updates accordingly
                if (newDist < minDistance[goingTo]) {
                    minDistance[goingTo] = newDist;
                    totalCost[goingTo] = newCost;
                    previous[goingTo] = next;
                }
            }
        } 
        

        
        
        // Reverses the path
        vector<int> path;
        for (int i = adj; i != -1; i = previous[i]) {
            path.push_back(i);
        }

        // Undo the reverse?? 
        vector<int> forwardPath;
        for (int i = path.size() - 1; i >= 0; i--) {
            forwardPath.push_back(path[i]);
        }
        path = forwardPath;

        int numOfStops = 2;
        if(path.size() >= 2) {

            numOfStops = path.size() - 2;

        }

        //Checks if the path to the destination exists
        if (minDistance[adj] == INT_MAX) {
            cout << "Shortest path from " << src  << " to " << dest << " with " << numOfStops << " stops: None\n";
            return;
        }

        if (path.empty() || path[0] != curr) {
            cout << "Shortest path from " << src << " to " << dest << " with " << numOfStops << " stops: None\n";
            return;
        }
        
        cout << "Shortest path from " << src  << " to " << dest << " with " << numOfStops << " stops: ";
        for (int i = 0; i < path.size(); i++) {
            cout << vertices[path[i]].getData();
            if (i + 1 < path.size()) 
                cout << " -> ";
        }

        cout << ". The length is " << minDistance[adj] << ". The cost is " << totalCost[adj] << ".\n";
        
}
//////////////////////////////////////////////////////////////////////////////////////////////////


template <typename T>
void Graph<T>::directConnections () const {
        
    //Count how many vertices we have
    int n = vertices.size();
    if (n == 0) {
        cout << "No flights found :(";
        return;
    }
    
    //Initialize the vector as 0
    vector<int> inDirect(n, 0); 
    vector<int> outDirect(n, 0);
    
    //count the flights going out of an irport
    for (int i = 0 ; i < n; i++) {
        outDirect[i] = edges[i].size();
    }

    //count the number of flights going into an airport
    for (int i = 0; i < n; i++) {
        for (const Edge& edgy : edges[i]) { 
            inDirect[edgy.dest] += 1;
        }
    }

    //Create the basis for the ranked direct flights to be put into
    vector<int> rankedDirect(n);
    for (int i = 0; i < n; i++) {
        rankedDirect[i] = i;
    }

    for(int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int rankTemp1 = inDirect[rankedDirect[j]] + outDirect[rankedDirect[j]];
            int rankTemp2 = inDirect[rankedDirect[j+1]] + outDirect[rankedDirect[j+1]];

            if (rankTemp1<rankTemp2) {
                int rank = rankedDirect[j];
                rankedDirect[j] = rankedDirect[j+1];
                rankedDirect[j+1] = rank;
            }
        }
    }

    cout << "Airport   Connections" << endl;
    for (int i = 0; i < n; i++) {
        int rankedIndex = rankedDirect[i];
        int total = inDirect[rankedIndex] + outDirect[rankedIndex];
        cout << vertices[rankedIndex].getData() << "       " << total << endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//Inserts an undirected edge
template <typename T>
void Graph<T>::add_undirected_edge(const Vertex<T>& ver1, const Vertex<T>& ver2, int cost) {
    add_edge(ver1, ver2, 0, cost);
    add_edge(ver2, ver1, 0, cost);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Graph<T> Graph<T>::createUndirectedGraph() const {
    Graph<T> Gu;
    int n = vertices.size();
    //If no airports, we are sad
    if (n==0)
        return Gu;

    //Makes a new vertex for each airport and puts it in Gu
    for (int i = 0; i < n; i++) {
        Vertex<T> temp = vertices[i];
        Gu.insert_vertex(temp, airportCities[i]);
    }

    //Create a vector that will be used to store the minCost of every pathway
    vector<vector<long>> minCost(n, vector<long>(n, INT_MAX));

    //Find which pathway has the shortest cost
    for (int i = 0; i < n; i++) {
        for (const Edge& edgy : edges[i]) {
            int currVer = edgy.dest;
            if(edgy.cost < minCost[i][currVer]) 
                minCost[i][currVer] = edgy.cost;
            if(edgy.cost < minCost[currVer][i]) 
                minCost[currVer][i] = edgy.cost;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int k = i + 1; k < n; k++) {
            if(minCost[i][k] != INT_MAX) { //Make sure the path actually exists
                long costIChooseYou = minCost[i][k];
                Vertex<T> ver1 = vertices[i];
                Vertex<T> ver2 = vertices[k];

                Gu.add_undirected_edge(ver1, ver2, costIChooseYou);
            }
        }
    }
    return Gu;
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////



template <typename T>

Graph<T> Graph<T>::prim() const {
    Graph<T> Gu = createUndirectedGraph(); 

    int n = Gu.vertices.size();

    if (n == 0) {
        cout << "No flights found :(";
        return Gu;
    }
    //Create a set MSTVertices that keeps track of vertices already included in MST
    vector<bool> visited (n, 0); //Will mark if it's been visited yet or not

    //Assign a key value to all vertices in the input graph. Initialize all key values as INFINITE
    //Assign key value as 0 for the first vertex so that it is picked first.
    vector<long> minCost(n, INT_MAX); //Tracks the minimum costs
    vector<int> parent (n, -1); //Tracks the parent the search is from

    minCost[0] = 0;

    long totalCost = 0;

    //While MSTVertices doesn’t include all vertices
    for (int i = 0; i < n; i++){
        //Pick a vertex u which is not there in MSTVertices and has minimum key value
        int u = -1;
        long minPath = INT_MAX;
        
        //find  the vertex with the smallest cost
        for (int k = 0; k < n ; k++) {
            if(!visited[k] && minCost[k] < minPath) {
                minPath = minCost[k];
                u = k;
            }
        }
        if (u == -1) //If we cycle through everything and it's still -1, just don't
            break;
        
        visited[u] = 1;
        totalCost += minCost[u]; //Update total cost
        
        //Update key value of all adjacent vertices of u.
        for (const Edge& edgy : Gu.edges[u]) {
            int goingTo = edgy.dest;

            //Make sure that the vertex should be included rn
            if(!visited[goingTo] && edgy.cost < minCost[goingTo]) {
                minCost[goingTo] = edgy.cost; //That is a much better deal :O let's do this one
                parent[goingTo] = u; //never forget where you come from =w=

            }
        }
    }

    //Prints the tree in the required format
    cout << "Minimal Spanning Tree:\n";
    cout << "Edge                          Weight\n";
    
    for(int i = 0; i < n; i++) {
        if (parent[i] != -1) {
            cout << vertices[parent[i]].getData() << " - " << vertices[i].getData() << "                        " << minCost[i] << endl;
        }
    }

    cout << "\n Total Cost of MST: " << totalCost << endl;

    return Gu;
    
} 


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


template <typename T>
Graph<T> Graph<T>::kruskal(){

    int n = vertices.size();

    Graph<T> Gu = createUndirectedGraph();
    Edge edgy2;

    // checks for flights
    if (n == 0) {
        cout << "No flights found :(";
        return Gu;
    }

    vector<vector<long>> minCost(n, vector<long>(n, INT_MAX));

    // Used to get minCost
    for (int i = 0; i < n; i++) {
        for (const Edge& edgy : edges[i]) {
            int currVer = edgy.dest;
            if(edgy.cost < minCost[i][currVer]) 
                minCost[i][currVer] = edgy.cost;
            if(edgy.cost < minCost[currVer][i]) 
                minCost[currVer][i] = edgy.cost;
        }
    }

    

    //Finds the total amount of edges
    int totalEdges = 0;
    for(int i = 0; i < n; i++){
        
        for(int j = i + 1; j < n; j++){

            if(minCost[i][j] != INT_MAX){
                totalEdges++;
            }

        }

    }

 
    vector<Edge> sortedEdges;
    
    // Sorts the Edges by minimum
    for (int k = 0; k < totalEdges; k++) {
     
        long cost = INT_MAX;
        int minU = -1;
        int minV = -1;


        for(int i = 0; i < n; i++){

            for (int j = i + 1; j < n; j++){
                
                if(minCost[i][j] < cost){

                    cost = minCost[i][j];

                    minU = i;
                    minV = j;

                }

            }

        }
        //saves edge information
        edgy2.src = minU;
        edgy2.dest = minV;
        edgy2.cost = cost;
        //pushes it
        sortedEdges.push_back(edgy2);
        //prevents the edge from being pushed again
        minCost[minU][minV] = INT_MAX;
        minCost[minV][minU] = INT_MAX;

    }

    //gives the vertex's numbers to keep track of them
    vector<int> vertexNum(n);
    for(int i = 0; i < n; i++){

        vertexNum[i] = i;

    }

    //keeps track of edges visited
    int edgesUsed = 0;
    
    for(auto &edgy3: sortedEdges){

        int u = edgy3.src;
        int v = edgy3.dest;

        //skip when u and v are the same to avoid making a cycle
        if(vertexNum[u] == vertexNum[v]){

            continue;

        } else{
            // adds the edge and keeps track of edges used
            // and then connects vertices with edges
            Gu.add_edge(vertices[u], vertices[v], 0, edgy3.cost);
            edgesUsed++;

            
            int vnum = vertexNum[v];
            int unum = vertexNum[u];


            for(int i = 0; i < n; i++){

                if(vertexNum[i] == vnum){

                    vertexNum[i] = unum;

                }

            }

            //Stops the function when MST has been created
            if(edgesUsed == n - 1){

                break;

            }


        }


    }

  
    long totalCost = 0;

    //Prints the tree in the required format
    cout << "Minimal Spanning Tree:\n";
    cout << "Edge                          Weight\n";
    
    for(int i = 0; i < n; i++) {
        
        for(const Edge& edgy4 : Gu.edges[i]){

            if(i < edgy4.dest){

                cout << Gu.vertices[i].getData() << "-" << Gu.vertices[edgy4.dest].getData() << "                          " << edgy4.cost << endl;
                totalCost += edgy4.cost; // Finds total cost
            }

        }

    }

    cout << "Total MST Cost: " << totalCost << endl;

    return Gu;



}
