#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

vector <vector<char>> SeperateData(const char* line){

    vector<vector<char>> data;
    vector<char> temp;
    int numOfQuotes = 0; // keeps track of opening and end quotes


    // Goes through each line and seperates it at quotes and commas
    for(int i = 0; line[i] != '\0'; i++){

        //checks by each character
        char c = line[i];

        // checks if the current character is a quote
        if(c == '"'){
            
            numOfQuotes++;

            // checks for the end quote then pushes the data into the vector and clears temporary vector
            if(numOfQuotes == 2){

                data.push_back(temp);
                temp.clear();
                numOfQuotes++;
            }
        // Continues to push if the end quote hasent been found
        }else if(numOfQuotes == 1){

            temp.push_back(c);

        //When the quote ends the comma after will be ignored
        }else if(c == ',' && numOfQuotes == 3){

            numOfQuotes = 0;
        // Checks for commas outside quotes and pushes into data vector and clear the temporary one
        }else if(c == ','){

            data.push_back(temp);
            temp.clear();

        //no quotes or commas then pushes into temporary vector
        } else{
            temp.push_back(c);
        }
    }


  // pushes the last of the data
    data.push_back(temp);

    //returns the vector with everything seperated
    return data;

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
