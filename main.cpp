#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "Graph.cpp"
#include "MinHeap.cpp"
#include "Queue.cpp"
#include "Stack.cpp"
using namespace std;



// Seperates the line by commas and quotes
template <typename T>
vector <vector<T>> SeperateData(const T* line){

    vector<vector<T>> info;
    vector<T> temp;
    int numOfQuotes = 0; // keeps track of opening and end quotes


    // Goes through each line and seperates it at quotes and commas
    for(int i = 0; line[i] != '\0'; i++){

        //checks by each character
        T c = line[i];

        // checks if the current character is a quote
        if(c == '"'){
            
            numOfQuotes++;

            // checks for the end quote then pushes the info into the vector and clears temporary vector
            if(numOfQuotes == 2){

                info.push_back(temp);
                temp.clear();
                numOfQuotes++;
            }
        // Continues to push if the end quote hasent been found
        }else if(numOfQuotes == 1){

            temp.push_back(c);

        //When the quote ends the comma after will be ignored
        }else if(c == ',' && numOfQuotes == 3){

            numOfQuotes = 0;
        // Checks for commas outside quotes and pushes into info vector and clear the temporary one
        }else if(c == ','){

            info.push_back(temp);
            temp.clear();

        //no quotes or commas then pushes into temporary vector
        } else{
            temp.push_back(c);
        }
    }


  // pushes the last of the info
    info.push_back(temp);

    //returns the vector with everything seperated
    return info;

}

int main(){

    //opens file
   const char* filename = "airports.csv";
   ifstream file(filename);

   //returns error if file could not open
   if(!file.is_open()){

    cout << "File could not open" << endl;
    return 1;

   }

   char line[12000];
   bool firstLine = true;  
   
    vector<vector<vector<char>>> allinOtoD;
    Graph<vector<vector<char>>> graph;
    
   // reads lines from file
   while(file.getline(line, sizeof(line))){


    // Skips column headings
        if(firstLine){

            firstLine = false;
            continue;

        }

        // seperates lines and saves them into a vector
        vector<vector<char>> section = SeperateData(line);

        Vertex<vector<vector<char>>> line(section);

        graph.insert_vertex(line);

         vector<vector<char>> OtoD;

        
        OtoD.push_back(section[0]);
        OtoD.push_back(section[1]);

        allinOtoD.push_back(OtoD);






        /*
        // prints the vector
       for(int i = 0; i < section.size(); ++i){ // prints the sections

            //cout << "section"<< i + 1 << ": ";

            for(int j = 0; j < section[i].size(); ++j){ // prints the words
                cout << section[i][j];
                
            }

            cout  << endl;

        }

        cout  << endl; 

   }
    
   */


       for(int i = 0; i < allinOtoD.size(); ++i){ // prints the sections

            //cout << "section"<< i + 1 << ": ";

            for(int j = 0; j < allinOtoD[i].size(); ++j){ // prints the words
                
                string field(allinOtoD[i][j].begin(), allinOtoD[i][j].end());
                cout << field << " ";
                
            }

            cout  << endl;

        }

}

   file.close();

    return 0;

}


