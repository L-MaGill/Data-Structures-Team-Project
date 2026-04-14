#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

vector <vector<char>> CSVLine(const char* line){

    vector<vector<char>> fields;
    vector<char> current;
    bool hasQuotes = false;

    
    for(int i = 0; line[i] != '\0'; i++){

        char c = line[i];

        if(c == '"'){
            hasQuotes = !hasQuotes;
            
        }else if(c == ','){

            current.push_back('\0');
            fields.push_back(current);
            current.clear();

        } else{
            current.push_back(c);
        }
    }


    current.push_back('\0');
    fields.push_back(current);

    return fields;

}

int main(){

   const char* filename = "airports.csv";
   ifstream file(filename);

   if(!file.is_open()){

    cout << "File could not open" << endl;
    return 1;

   }

   char line[1024];
   while(file.getline(line, sizeof(line))){

        vector<vector<char>> fields = CSVLine(line);

        for(int i = 0; i < fields.size(); ++i){

            cout << "Field"<< i + 1 << ": ";

            for(int j = 0; fields[i][j] != '\0'; ++j){
                cout << fields[i][j] ;
                
            }

            cout  << endl;

        }

   }

   file.close();
    return 0;

}
