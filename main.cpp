#include "Graph.h"
#include "Vertex.h"
#include "Graph.cpp"

#include <string>
#include <fstream>
#include <vector>
#include <iostream>



int main(){

    ifstream file("airplanes.csv");

    if(!file.is_open()){

        cout << "File could not open" << endl;
        return 1;
    }

    string line;

    while(getline(file, line)){

        vector<string> fields = Quotes(line);

        for(int i = 0; i < fields.size(); i++){

            cout << field[i] << " " << endl;

        }

    }

    file.close();


    return 0;

}
