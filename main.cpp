#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

vector <vector<char>> CSVLine(const char* line){

    vector<vector<char>> fields;
    vector<char> current;
    bool hasQuotes = false;

    // Goes through each line and seperates it at quotes and commas
    for(int i = 0; line[i] != '\0'; i++){

        char c = line[i];

        // checks if the current character is a quote
        if(c == '"'){
            hasQuotes = !hasQuotes;
            
        }else if(c == ','){

            current.push_back('\0');
            fields.push_back(current);
            current.clear();

        //no quotes or commas then pushes into temporary vector
        } else{
            temp.push_back(c);
        }
    }


    current.push_back('\0');
    fields.push_back(current);

    return fields;

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
  
   // reads lines from file
   while(file.getline(line, sizeof(line))){


    // Skips column headings
        if(firstLine){

            firstLine = false;
            continue;

        }


        // seperates lines and saves them into a vector
        vector<vector<char>> section = SeperateData(line);


        // prints the vector
       for(int i = 0; i < section.size(); ++i){

            //cout << "section"<< i + 1 << ": ";

            for(int j = 0; j < section[i].size(); ++j){
                cout << section[i][j];
                
            }

            cout  << endl;

        }

        cout  << endl; 

   }
   
   file.close();

    return 0;

}
