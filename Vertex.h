#ifndef VERTEX_H
#define VERTEX_H

template <typename T>
class Vertex {
public:
    //Creates airport
    Vertex(const T& d = T()) : data(d), visited(false) {}

    //Returns airport code
    const T& getData() const {return data; }

    //Have we been to this airport already?
    bool getVisited() const {return visited; }

    //We just visited this airport!!
    void setVisited(bool v) { visited = v; }

private:
    T data;
    bool visited;
};

#endif