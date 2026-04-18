#ifndef EDGE_H
#define EDGE_H

class Edge {
public:
    int src; //Starting point
    int dest; //Ending point
    int distance; //Miles (We gotta be greedy)
    int cost; //Price (We gotta be even greedier)

    //Makes a new edge
    Edge(int src = 0, int dest = 0, int dist = 0, int cost = 0) : 
        src(src), dest(dest), weight(weight), cost(cost) {}


    //Compares costs
    bool operator<(const Edge& other) const {
        if(this->cost < other.cost) {
            return true;
        }

        return false;
    }

};

#endif
